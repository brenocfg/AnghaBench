#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
struct TYPE_8__ {int flags; int fd; } ;
typedef  TYPE_1__ redisContext ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ EHOSTUNREACH ; 
 scalar_t__ EINPROGRESS ; 
 int REDIS_BLOCK ; 
 int REDIS_CONNECTED ; 
 int REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_OTHER ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  __redisSetError (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  redisContextCloseFd (TYPE_1__*) ; 
 int redisContextWaitReady (TYPE_1__*,struct timeval const*) ; 
 int redisSetBlocking (TYPE_1__*,int) ; 
 int redisSetTcpNoDelay (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static int _redisContextConnectTcp(redisContext *c, const char *addr, int port,
                                   const struct timeval *timeout,
                                   const char *source_addr) {
    int s, rv;
    char _port[6];  /* strlen("65535"); */
    struct addrinfo hints, *servinfo, *bservinfo, *p, *b;
    int blocking = (c->flags & REDIS_BLOCK);

    snprintf(_port, 6, "%d", port);
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /* Try with IPv6 if no IPv4 address was found. We do it in this order since
     * in a Redis client you can't afford to test if you have IPv6 connectivity
     * as this would add latency to every connect. Otherwise a more sensible
     * route could be: Use IPv6 if both addresses are available and there is IPv6
     * connectivity. */
    if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {
         hints.ai_family = AF_INET6;
         if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {
            __redisSetError(c,REDIS_ERR_OTHER,gai_strerror(rv));
            return REDIS_ERR;
        }
    }
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((s = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
            continue;

        c->fd = s;
        if (redisSetBlocking(c,0) != REDIS_OK)
            goto error;
        if (source_addr) {
            int bound = 0;
            /* Using getaddrinfo saves us from self-determining IPv4 vs IPv6 */
            if ((rv = getaddrinfo(source_addr, NULL, &hints, &bservinfo)) != 0) {
                char buf[128];
                snprintf(buf,sizeof(buf),"Can't get addr: %s",gai_strerror(rv));
                __redisSetError(c,REDIS_ERR_OTHER,buf);
                goto error;
            }
            for (b = bservinfo; b != NULL; b = b->ai_next) {
                if (bind(s,b->ai_addr,b->ai_addrlen) != -1) {
                    bound = 1;
                    break;
                }
            }
            freeaddrinfo(bservinfo);
            if (!bound) {
                char buf[128];
                snprintf(buf,sizeof(buf),"Can't bind socket: %s",strerror(errno));
                __redisSetError(c,REDIS_ERR_OTHER,buf);
                goto error;
            }
        }
        if (connect(s,p->ai_addr,p->ai_addrlen) == -1) {
            if (errno == EHOSTUNREACH) {
                redisContextCloseFd(c);
                continue;
            } else if (errno == EINPROGRESS && !blocking) {
                /* This is ok. */
            } else {
                if (redisContextWaitReady(c,timeout) != REDIS_OK)
                    goto error;
            }
        }
        if (blocking && redisSetBlocking(c,1) != REDIS_OK)
            goto error;
        if (redisSetTcpNoDelay(c) != REDIS_OK)
            goto error;

        c->flags |= REDIS_CONNECTED;
        rv = REDIS_OK;
        goto end;
    }
    if (p == NULL) {
        char buf[128];
        snprintf(buf,sizeof(buf),"Can't create socket: %s",strerror(errno));
        __redisSetError(c,REDIS_ERR_OTHER,buf);
        goto error;
    }

error:
    rv = REDIS_ERR;
end:
    freeaddrinfo(servinfo);
    return rv;  // Need to return REDIS_OK if alright
}
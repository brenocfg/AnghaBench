#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ws_ctx_t ;
typedef  int /*<<< orphan*/  taddr ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  daemon; scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  do_proxy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  handler_emsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handler_msg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int resolve_host (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ settings ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_host ; 
 int /*<<< orphan*/  target_port ; 
 char* traffic_legend ; 

void proxy_handler(ws_ctx_t *ws_ctx) {
    int tsock = 0;
    struct sockaddr_in taddr;

    handler_msg("connecting to: %s:%d\n", target_host, target_port);

    tsock = socket(AF_INET, SOCK_STREAM, 0);
    if (tsock < 0) {
        handler_emsg("Could not create target socket: %s\n",
                     strerror(errno));
        return;
    }
    bzero((char *) &taddr, sizeof(taddr));
    taddr.sin_family = AF_INET;
    taddr.sin_port = htons(target_port);

    /* Resolve target address */
    if (resolve_host(&taddr.sin_addr, target_host) < -1) {
        handler_emsg("Could not resolve target address: %s\n",
                     strerror(errno));
    }

    if (connect(tsock, (struct sockaddr *) &taddr, sizeof(taddr)) < 0) {
        handler_emsg("Could not connect to target: %s\n",
                     strerror(errno));
        close(tsock);
        return;
    }

    if ((settings.verbose) && (! settings.daemon)) {
        printf("%s", traffic_legend);
    }

    do_proxy(ws_ctx, tsock);

    shutdown(tsock, SHUT_RDWR);
    close(tsock);
}
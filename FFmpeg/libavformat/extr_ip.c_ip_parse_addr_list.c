#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct sockaddr_storage {int /*<<< orphan*/  member_0; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  source_addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  av_dynarray2_add (void**,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_get_token (char const**,char*) ; 
 struct addrinfo* ff_ip_resolve_host (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_parse_addr_list(void *log_ctx, const char *buf,
                              struct sockaddr_storage **address_list_ptr,
                              int *address_list_size_ptr)
{
    struct addrinfo *ai = NULL;

    /* Resolve all of the IPs */

    while (buf && buf[0]) {
        char* host = av_get_token(&buf, ",");
        if (!host)
            return AVERROR(ENOMEM);

        ai = ff_ip_resolve_host(log_ctx, host, 0, SOCK_DGRAM, AF_UNSPEC, 0);
        av_freep(&host);

        if (ai) {
            struct sockaddr_storage source_addr = {0};
            memcpy(&source_addr, ai->ai_addr, ai->ai_addrlen);
            freeaddrinfo(ai);
            av_dynarray2_add((void **)address_list_ptr, address_list_size_ptr, sizeof(source_addr), (uint8_t *)&source_addr);
            if (!*address_list_ptr)
                return AVERROR(ENOMEM);
        } else {
            return AVERROR(EINVAL);
        }

        if (*buf)
            buf++;
    }

    return 0;
}
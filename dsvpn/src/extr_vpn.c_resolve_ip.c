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
struct addrinfo {scalar_t__ ai_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/ * ai_addr; int /*<<< orphan*/  ai_socktype; scalar_t__ ai_flags; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int getnameinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int resolve_ip(char *ip, size_t sizeof_ip, const char *ip_or_name)
{
    struct addrinfo hints, *res;
    int             eai;

    memset(&hints, 0, sizeof hints);
    hints.ai_flags    = 0;
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_addr     = NULL;
    if ((eai = getaddrinfo(ip_or_name, NULL, &hints, &res)) != 0 ||
        (res->ai_family != AF_INET && res->ai_family != AF_INET6) ||
        (eai = getnameinfo(res->ai_addr, res->ai_addrlen, ip, (socklen_t) sizeof_ip, NULL, 0,
                           NI_NUMERICHOST | NI_NUMERICSERV)) != 0) {
        fprintf(stderr, "Unable to resolve [%s]: [%s]\n", ip_or_name, gai_strerror(eai));
        return -1;
    }
    return 0;
}
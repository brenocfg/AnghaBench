#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct hostent {scalar_t__ h_addrtype; scalar_t__* h_addr_list; } ;
typedef  int /*<<< orphan*/  enet_uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ ENetAddress ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 struct hostent* gethostbyname (char const*) ; 
 int /*<<< orphan*/  inet_aton (char const*,struct in_addr*) ; 

int
enet_address_set_host (ENetAddress * address, const char * name)
{
    struct hostent * hostEntry = NULL;
#ifdef HAS_GETHOSTBYNAME_R
    struct hostent hostData;
    char buffer [2048];
    int errnum;

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__EMSCRIPTEN__)
    gethostbyname_r (name, & hostData, buffer, sizeof (buffer), & hostEntry, & errnum);
#else
    hostEntry = gethostbyname_r (name, & hostData, buffer, sizeof (buffer), & errnum);
#endif
#else
    hostEntry = gethostbyname (name);
#endif

    if (hostEntry == NULL ||
        hostEntry -> h_addrtype != AF_INET)
    {
#ifdef HAS_INET_PTON
        if (! inet_pton (AF_INET, name, & address -> host))
#else
        if (! inet_aton (name, (struct in_addr *) & address -> host))
#endif
            return -1;
        return 0;
    }

    address -> host = * (enet_uint32 *) hostEntry -> h_addr_list [0];

    return 0;
}
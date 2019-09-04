#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct hostent {int /*<<< orphan*/  h_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ ENetAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int enet_address_get_host_ip (TYPE_1__ const*,char*,size_t) ; 
 struct hostent* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 

int
enet_address_get_host (const ENetAddress * address, char * name, size_t nameLength)
{
    struct in_addr in;
    struct hostent * hostEntry = NULL;
#ifdef HAS_GETHOSTBYADDR_R
    struct hostent hostData;
    char buffer [2048];
    int errnum;

    in.s_addr = address -> host;

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__EMSCRIPTEN__)
    gethostbyaddr_r ((char *) & in, sizeof (struct in_addr), AF_INET, & hostData, buffer, sizeof (buffer), & hostEntry, & errnum);
#else
    hostEntry = gethostbyaddr_r ((char *) & in, sizeof (struct in_addr), AF_INET, & hostData, buffer, sizeof (buffer), & errnum);
#endif
#else
    in.s_addr = address -> host;

    hostEntry = gethostbyaddr ((char *) & in, sizeof (struct in_addr), AF_INET);
#endif

    if (hostEntry == NULL)
      return enet_address_get_host_ip (address, name, nameLength);

    strncpy (name, hostEntry -> h_name, nameLength);

    return 0;
}
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
struct TYPE_3__ {int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ ENetAddress ;

/* Variables and functions */
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

int
enet_address_get_host_ip (const ENetAddress * address, char * name, size_t nameLength)
{
#ifdef HAS_INET_NTOP
    if (inet_ntop (AF_INET, & address -> host, name, nameLength) == NULL)
#else
    char * addr = inet_ntoa (* (struct in_addr *) & address -> host);
    if (addr != NULL)
        strncpy (name, addr, nameLength);
    else
#endif
        return -1;
    return 0;
}
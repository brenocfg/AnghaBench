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
typedef  int I_32 ;

/* Variables and functions */
#define  HYADDR_FAMILY_AFINET4 129 
#define  HYADDR_FAMILY_AFINET6 128 
 int OS_AF_INET4 ; 
 int OS_AF_INET6 ; 
 int OS_AF_UNSPEC ; 

I_32 map_addr_family_Hy_to_OS (I_32 addr_family)
{
    switch (addr_family)
    {
        case HYADDR_FAMILY_AFINET4:
            return OS_AF_INET4;
        case HYADDR_FAMILY_AFINET6:
            return OS_AF_INET6;
    }
    return OS_AF_UNSPEC;
}
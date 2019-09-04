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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {struct in_addr client_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* S_netboot_info_p ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
netboot_iaddr(struct in_addr * iaddr_p)
{
    if (S_netboot_info_p == NULL)
	return (FALSE);

    *iaddr_p = S_netboot_info_p->client_ip;
    return (TRUE);
}
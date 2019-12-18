#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct llinfo_arp {TYPE_1__* la_llreach; } ;
typedef  TYPE_2__* route_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {struct llinfo_arp* rt_llinfo; } ;
struct TYPE_4__ {scalar_t__ lr_probes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
arp_is_entry_probing (route_t p_route)
{
	struct llinfo_arp *llinfo = p_route->rt_llinfo;

	if (llinfo != NULL &&
	    llinfo->la_llreach != NULL &&
	    llinfo->la_llreach->lr_probes != 0)
		return (TRUE);

	return (FALSE);
}
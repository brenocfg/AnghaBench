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
struct pnp_option {int dummy; } ;

/* Variables and functions */
#define  PNP_RES_PRIORITY_ACCEPTABLE 130 
#define  PNP_RES_PRIORITY_FUNCTIONAL 129 
#define  PNP_RES_PRIORITY_PREFERRED 128 
 int pnp_option_priority (struct pnp_option*) ; 

char *pnp_option_priority_name(struct pnp_option *option)
{
	switch (pnp_option_priority(option)) {
	case PNP_RES_PRIORITY_PREFERRED:
		return "preferred";
	case PNP_RES_PRIORITY_ACCEPTABLE:
		return "acceptable";
	case PNP_RES_PRIORITY_FUNCTIONAL:
		return "functional";
	}
	return "invalid";
}
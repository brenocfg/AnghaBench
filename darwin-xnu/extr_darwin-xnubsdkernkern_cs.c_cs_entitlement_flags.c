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
typedef  int uint32_t ;
struct proc {int p_csflags; } ;

/* Variables and functions */
 int CS_ENTITLEMENT_FLAGS ; 

uint32_t
cs_entitlement_flags(struct proc *p)
{
	return (p->p_csflags & CS_ENTITLEMENT_FLAGS);
}
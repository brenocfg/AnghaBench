#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sh_addr; } ;
struct TYPE_6__ {TYPE_1__ ps_sh; } ;
typedef  TYPE_2__ PE_Scn ;

/* Variables and functions */

__attribute__((used)) static int
cmp_scn(PE_Scn *a, PE_Scn *b)
{

	if (a->ps_sh.sh_addr < b->ps_sh.sh_addr)
		return (-1);
	else if (a->ps_sh.sh_addr == b->ps_sh.sh_addr)
		return (0);
	else
		return (1);
}
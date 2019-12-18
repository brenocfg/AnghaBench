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
typedef  int /*<<< orphan*/  dt_idhash_t ;
struct TYPE_3__ {int di_flags; } ;
typedef  TYPE_1__ dt_ident_t ;

/* Variables and functions */
 int DT_IDFLG_DIFR ; 
 int DT_IDFLG_DIFW ; 

__attribute__((used)) static int
dt_countvar(dt_idhash_t *dhp, dt_ident_t *idp, void *data)
{
	size_t *np = data;

	if (idp->di_flags & (DT_IDFLG_DIFR | DT_IDFLG_DIFW))
		(*np)++; /* include variable in vartab */

	return (0);
}
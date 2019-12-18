#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uchar_t ;
struct TYPE_10__ {int /*<<< orphan*/  cte_value; int /*<<< orphan*/  cte_name; } ;
typedef  TYPE_2__ ctf_enum_t ;
struct TYPE_12__ {int /*<<< orphan*/  dmd_name; int /*<<< orphan*/  dmd_value; } ;
struct TYPE_9__ {TYPE_4__ dtu_members; } ;
struct TYPE_11__ {TYPE_1__ dtd_u; } ;
typedef  TYPE_3__ ctf_dtdef_t ;
typedef  TYPE_4__ ctf_dmdef_t ;
typedef  int /*<<< orphan*/  cte ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* ctf_list_next (TYPE_4__*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uchar_t *
ctf_copy_emembers(ctf_dtdef_t *dtd, uint_t soff, uchar_t *t)
{
	ctf_dmdef_t *dmd = ctf_list_next(&dtd->dtd_u.dtu_members);
	ctf_enum_t cte;

	for (; dmd != NULL; dmd = ctf_list_next(dmd)) {
		cte.cte_name = soff;
		cte.cte_value = dmd->dmd_value;
		soff += strlen(dmd->dmd_name) + 1;
		bcopy(&cte, t, sizeof (cte));
		t += sizeof (cte);
	}

	return (t);
}
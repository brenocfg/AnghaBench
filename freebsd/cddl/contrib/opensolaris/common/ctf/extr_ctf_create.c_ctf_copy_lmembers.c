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
typedef  scalar_t__ ushort_t ;
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uchar_t ;
typedef  int /*<<< orphan*/  ctlm ;
struct TYPE_10__ {int /*<<< orphan*/  ctlm_offsetlo; int /*<<< orphan*/  ctlm_offsethi; scalar_t__ ctlm_pad; scalar_t__ ctlm_type; scalar_t__ ctlm_name; } ;
typedef  TYPE_2__ ctf_lmember_t ;
struct TYPE_12__ {int /*<<< orphan*/  dmd_offset; scalar_t__ dmd_type; scalar_t__ dmd_name; } ;
struct TYPE_9__ {TYPE_4__ dtu_members; } ;
struct TYPE_11__ {TYPE_1__ dtd_u; } ;
typedef  TYPE_3__ ctf_dtdef_t ;
typedef  TYPE_4__ ctf_dmdef_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_OFFSET_TO_LMEMHI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_OFFSET_TO_LMEMLO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* ctf_list_next (TYPE_4__*) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static uchar_t *
ctf_copy_lmembers(ctf_dtdef_t *dtd, uint_t soff, uchar_t *t)
{
	ctf_dmdef_t *dmd = ctf_list_next(&dtd->dtd_u.dtu_members);
	ctf_lmember_t ctlm;

	for (; dmd != NULL; dmd = ctf_list_next(dmd)) {
		if (dmd->dmd_name) {
			ctlm.ctlm_name = soff;
			soff += strlen(dmd->dmd_name) + 1;
		} else
			ctlm.ctlm_name = 0;

		ctlm.ctlm_type = (ushort_t)dmd->dmd_type;
		ctlm.ctlm_pad = 0;
		ctlm.ctlm_offsethi = CTF_OFFSET_TO_LMEMHI(dmd->dmd_offset);
		ctlm.ctlm_offsetlo = CTF_OFFSET_TO_LMEMLO(dmd->dmd_offset);

		bcopy(&ctlm, t, sizeof (ctlm));
		t += sizeof (ctlm);
	}

	return (t);
}
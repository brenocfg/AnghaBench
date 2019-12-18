#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_16__ {int ctf_flags; } ;
typedef  TYPE_3__ ctf_file_t ;
struct TYPE_18__ {int /*<<< orphan*/  ctr_index; int /*<<< orphan*/  ctr_contents; } ;
struct TYPE_15__ {TYPE_5__ dtu_arr; } ;
struct TYPE_14__ {int /*<<< orphan*/  ctt_info; } ;
struct TYPE_17__ {TYPE_2__ dtd_u; TYPE_1__ dtd_data; } ;
typedef  TYPE_4__ ctf_dtdef_t ;
typedef  TYPE_5__ ctf_arinfo_t ;

/* Variables and functions */
 scalar_t__ CTF_INFO_KIND (int /*<<< orphan*/ ) ; 
 scalar_t__ CTF_K_ARRAY ; 
 int /*<<< orphan*/  ECTF_BADID ; 
 int /*<<< orphan*/  ECTF_RDONLY ; 
 int LCTF_DIRTY ; 
 int LCTF_RDWR ; 
 TYPE_4__* ctf_dtd_lookup (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ctf_lookup_by_id (TYPE_3__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_ref_dec (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_ref_inc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ctf_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 

int
ctf_set_array(ctf_file_t *fp, ctf_id_t type, const ctf_arinfo_t *arp)
{
	ctf_file_t *fpd;
	ctf_dtdef_t *dtd = ctf_dtd_lookup(fp, type);

	if (!(fp->ctf_flags & LCTF_RDWR))
		return (ctf_set_errno(fp, ECTF_RDONLY));

	if (dtd == NULL || CTF_INFO_KIND(dtd->dtd_data.ctt_info) != CTF_K_ARRAY)
		return (ctf_set_errno(fp, ECTF_BADID));

	fpd = fp;
	if (ctf_lookup_by_id(&fpd, arp->ctr_contents) == NULL &&
	    ctf_dtd_lookup(fp, arp->ctr_contents) == NULL)
		return (ctf_set_errno(fp, ECTF_BADID));

	fpd = fp;
	if (ctf_lookup_by_id(&fpd, arp->ctr_index) == NULL &&
	    ctf_dtd_lookup(fp, arp->ctr_index) == NULL)
		return (ctf_set_errno(fp, ECTF_BADID));

	ctf_ref_dec(fp, dtd->dtd_u.dtu_arr.ctr_contents);
	ctf_ref_dec(fp, dtd->dtd_u.dtu_arr.ctr_index);
	fp->ctf_flags |= LCTF_DIRTY;
	dtd->dtd_u.dtu_arr = *arp;
	ctf_ref_inc(fp, arp->ctr_contents);
	ctf_ref_inc(fp, arp->ctr_index);

	return (0);
}
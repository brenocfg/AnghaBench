#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_10__ {int /*<<< orphan*/  ctr_index; int /*<<< orphan*/  ctr_contents; } ;
struct TYPE_8__ {TYPE_4__ dtu_arr; } ;
struct TYPE_7__ {scalar_t__ ctt_size; int /*<<< orphan*/  ctt_info; } ;
struct TYPE_9__ {TYPE_2__ dtd_u; TYPE_1__ dtd_data; } ;
typedef  TYPE_3__ ctf_dtdef_t ;
typedef  TYPE_4__ ctf_arinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  CTF_K_ARRAY ; 
 int /*<<< orphan*/  CTF_TYPE_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECTF_BADID ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ctf_add_generic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/ * ctf_dtd_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ctf_lookup_by_id (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_ref_inc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ctf_id_t
ctf_add_array(ctf_file_t *fp, uint_t flag, const ctf_arinfo_t *arp)
{
	ctf_dtdef_t *dtd;
	ctf_id_t type;
	ctf_file_t *fpd;

	if (arp == NULL)
		return (ctf_set_errno(fp, EINVAL));

	fpd = fp;
	if (ctf_lookup_by_id(&fpd, arp->ctr_contents) == NULL &&
	    ctf_dtd_lookup(fp, arp->ctr_contents) == NULL)
		return (ctf_set_errno(fp, ECTF_BADID));

	fpd = fp;
	if (ctf_lookup_by_id(&fpd, arp->ctr_index) == NULL &&
	    ctf_dtd_lookup(fp, arp->ctr_index) == NULL)
		return (ctf_set_errno(fp, ECTF_BADID));

	if ((type = ctf_add_generic(fp, flag, NULL, &dtd)) == CTF_ERR)
		return (CTF_ERR); /* errno is set for us */

	dtd->dtd_data.ctt_info = CTF_TYPE_INFO(CTF_K_ARRAY, flag, 0);
	dtd->dtd_data.ctt_size = 0;
	dtd->dtd_u.dtu_arr = *arp;
	ctf_ref_inc(fp, arp->ctr_contents);
	ctf_ref_inc(fp, arp->ctr_index);

	return (type);
}
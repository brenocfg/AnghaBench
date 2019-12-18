#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_7__ {int /*<<< orphan*/  ctt_info; } ;
typedef  TYPE_1__ ctf_type_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_8__ {int /*<<< orphan*/  cta_nelems; int /*<<< orphan*/  cta_index; int /*<<< orphan*/  cta_contents; } ;
typedef  TYPE_2__ ctf_array_t ;
struct TYPE_9__ {int /*<<< orphan*/  ctr_nelems; int /*<<< orphan*/  ctr_index; int /*<<< orphan*/  ctr_contents; } ;
typedef  TYPE_3__ ctf_arinfo_t ;

/* Variables and functions */
 int CTF_ERR ; 
 scalar_t__ CTF_K_ARRAY ; 
 int /*<<< orphan*/  ECTF_NOTARRAY ; 
 scalar_t__ LCTF_INFO_KIND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_get_ctt_size (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *,scalar_t__*) ; 
 TYPE_1__* ctf_lookup_by_id (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ctf_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ctf_array_info(ctf_file_t *fp, ctf_id_t type, ctf_arinfo_t *arp)
{
	ctf_file_t *ofp = fp;
	const ctf_type_t *tp;
	const ctf_array_t *ap;
	ssize_t increment;

	if ((tp = ctf_lookup_by_id(&fp, type)) == NULL)
		return (CTF_ERR); /* errno is set for us */

	if (LCTF_INFO_KIND(fp, tp->ctt_info) != CTF_K_ARRAY)
		return (ctf_set_errno(ofp, ECTF_NOTARRAY));

	(void) ctf_get_ctt_size(fp, tp, NULL, &increment);

	ap = (const ctf_array_t *)((uintptr_t)tp + increment);
	arp->ctr_contents = ap->cta_contents;
	arp->ctr_index = ap->cta_index;
	arp->ctr_nelems = ap->cta_nelems;

	return (0);
}
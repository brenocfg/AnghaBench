#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uchar_t ;
typedef  int ssize_t ;
struct TYPE_18__ {int /*<<< orphan*/  ctt_info; } ;
typedef  TYPE_2__ ctf_type_t ;
struct TYPE_19__ {int /*<<< orphan*/  ctm_type; } ;
typedef  TYPE_3__ ctf_member_t ;
struct TYPE_20__ {int /*<<< orphan*/  ctlm_type; } ;
typedef  TYPE_4__ ctf_lmember_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_21__ {TYPE_1__* ctf_dmodel; int /*<<< orphan*/  ctf_version; } ;
typedef  TYPE_5__ ctf_file_t ;
struct TYPE_22__ {int /*<<< orphan*/  ctr_contents; } ;
typedef  TYPE_6__ ctf_arinfo_t ;
struct TYPE_17__ {int ctd_pointer; int ctd_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
#define  CTF_K_ARRAY 133 
#define  CTF_K_ENUM 132 
#define  CTF_K_FUNCTION 131 
#define  CTF_K_POINTER 130 
#define  CTF_K_STRUCT 129 
#define  CTF_K_UNION 128 
 int CTF_LSTRUCT_THRESH ; 
 int /*<<< orphan*/  CTF_VERSION_1 ; 
 int const LCTF_INFO_KIND (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCTF_INFO_VLEN (TYPE_5__*,int /*<<< orphan*/ ) ; 
 size_t MAX (size_t,int) ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctf_array_info (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int ctf_get_ctt_size (TYPE_5__*,TYPE_2__ const*,int*,int*) ; 
 TYPE_2__* ctf_lookup_by_id (TYPE_5__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (TYPE_5__*,int /*<<< orphan*/ ) ; 

ssize_t
ctf_type_align(ctf_file_t *fp, ctf_id_t type)
{
	const ctf_type_t *tp;
	ctf_arinfo_t r;

	if ((type = ctf_type_resolve(fp, type)) == CTF_ERR)
		return (-1); /* errno is set for us */

	if ((tp = ctf_lookup_by_id(&fp, type)) == NULL)
		return (-1); /* errno is set for us */

	switch (LCTF_INFO_KIND(fp, tp->ctt_info)) {
	case CTF_K_POINTER:
	case CTF_K_FUNCTION:
		return (fp->ctf_dmodel->ctd_pointer);

	case CTF_K_ARRAY:
		if (ctf_array_info(fp, type, &r) == CTF_ERR)
			return (-1); /* errno is set for us */
		return (ctf_type_align(fp, r.ctr_contents));

	case CTF_K_STRUCT:
	case CTF_K_UNION: {
		uint_t n = LCTF_INFO_VLEN(fp, tp->ctt_info);
		ssize_t size, increment;
		size_t align = 0;
		const void *vmp;

		(void) ctf_get_ctt_size(fp, tp, &size, &increment);
		vmp = (uchar_t *)tp + increment;

		if (LCTF_INFO_KIND(fp, tp->ctt_info) == CTF_K_STRUCT)
			n = MIN(n, 1); /* only use first member for structs */

		if (fp->ctf_version == CTF_VERSION_1 ||
		    size < CTF_LSTRUCT_THRESH) {
			const ctf_member_t *mp = vmp;
			for (; n != 0; n--, mp++) {
				ssize_t am = ctf_type_align(fp, mp->ctm_type);
				align = MAX(align, am);
			}
		} else {
			const ctf_lmember_t *lmp = vmp;
			for (; n != 0; n--, lmp++) {
				ssize_t am = ctf_type_align(fp, lmp->ctlm_type);
				align = MAX(align, am);
			}
		}

		return (align);
	}

	case CTF_K_ENUM:
		return (fp->ctf_dmodel->ctd_int);

	default:
		return (ctf_get_ctt_size(fp, tp, NULL, NULL));
	}
}
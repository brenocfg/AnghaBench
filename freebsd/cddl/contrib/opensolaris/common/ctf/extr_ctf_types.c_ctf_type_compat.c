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
typedef  int uint_t ;
struct TYPE_5__ {int /*<<< orphan*/  ctt_name; } ;
typedef  TYPE_1__ ctf_type_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
typedef  int /*<<< orphan*/  ctf_encoding_t ;
struct TYPE_6__ {int /*<<< orphan*/  ctr_index; int /*<<< orphan*/  ctr_contents; int /*<<< orphan*/  ctr_nelems; } ;
typedef  TYPE_2__ ctf_arinfo_t ;

/* Variables and functions */
#define  CTF_K_ARRAY 135 
#define  CTF_K_ENUM 134 
#define  CTF_K_FLOAT 133 
#define  CTF_K_FORWARD 132 
#define  CTF_K_INTEGER 131 
#define  CTF_K_POINTER 130 
#define  CTF_K_STRUCT 129 
#define  CTF_K_UNION 128 
 int /*<<< orphan*/  bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ctf_array_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* ctf_lookup_by_id (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_type_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ctf_type_compat(ctf_file_t *lfp, ctf_id_t ltype,
    ctf_file_t *rfp, ctf_id_t rtype)
{
	const ctf_type_t *ltp, *rtp;
	ctf_encoding_t le, re;
	ctf_arinfo_t la, ra;
	uint_t lkind, rkind;

	if (ctf_type_cmp(lfp, ltype, rfp, rtype) == 0)
		return (1);

	ltype = ctf_type_resolve(lfp, ltype);
	lkind = ctf_type_kind(lfp, ltype);

	rtype = ctf_type_resolve(rfp, rtype);
	rkind = ctf_type_kind(rfp, rtype);

	if (lkind != rkind ||
	    (ltp = ctf_lookup_by_id(&lfp, ltype)) == NULL ||
	    (rtp = ctf_lookup_by_id(&rfp, rtype)) == NULL ||
	    strcmp(ctf_strptr(lfp, ltp->ctt_name),
	    ctf_strptr(rfp, rtp->ctt_name)) != 0)
		return (0);

	switch (lkind) {
	case CTF_K_INTEGER:
	case CTF_K_FLOAT:
		return (ctf_type_encoding(lfp, ltype, &le) == 0 &&
		    ctf_type_encoding(rfp, rtype, &re) == 0 &&
		    bcmp(&le, &re, sizeof (ctf_encoding_t)) == 0);
	case CTF_K_POINTER:
		return (ctf_type_compat(lfp, ctf_type_reference(lfp, ltype),
		    rfp, ctf_type_reference(rfp, rtype)));
	case CTF_K_ARRAY:
		return (ctf_array_info(lfp, ltype, &la) == 0 &&
		    ctf_array_info(rfp, rtype, &ra) == 0 &&
		    la.ctr_nelems == ra.ctr_nelems && ctf_type_compat(
		    lfp, la.ctr_contents, rfp, ra.ctr_contents) &&
		    ctf_type_compat(lfp, la.ctr_index, rfp, ra.ctr_index));
	case CTF_K_STRUCT:
	case CTF_K_UNION:
		return (ctf_type_size(lfp, ltype) == ctf_type_size(rfp, rtype));
	case CTF_K_ENUM:
	case CTF_K_FORWARD:
		return (1); /* no other checks required for these type kinds */
	default:
		return (0); /* should not get here since we did a resolve */
	}
}
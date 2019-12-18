#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_65__   TYPE_9__ ;
typedef  struct TYPE_64__   TYPE_8__ ;
typedef  struct TYPE_63__   TYPE_7__ ;
typedef  struct TYPE_62__   TYPE_6__ ;
typedef  struct TYPE_61__   TYPE_5__ ;
typedef  struct TYPE_60__   TYPE_4__ ;
typedef  struct TYPE_59__   TYPE_3__ ;
typedef  struct TYPE_58__   TYPE_2__ ;
typedef  struct TYPE_57__   TYPE_1__ ;
typedef  struct TYPE_56__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort_t ;
typedef  int uint_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_59__ {scalar_t__ ctt_type; int /*<<< orphan*/  ctt_info; int /*<<< orphan*/  ctt_name; } ;
typedef  TYPE_3__ ctf_type_t ;
typedef  scalar_t__ ctf_id_t ;
struct TYPE_60__ {scalar_t__ h_type; } ;
typedef  TYPE_4__ ctf_helem_t ;
typedef  int /*<<< orphan*/  ctf_hash_t ;
struct TYPE_61__ {scalar_t__ ctc_return; int /*<<< orphan*/  ctc_flags; int /*<<< orphan*/  ctc_argc; } ;
typedef  TYPE_5__ ctf_funcinfo_t ;
struct TYPE_65__ {scalar_t__ dmd_type; } ;
struct TYPE_63__ {scalar_t__ ctr_contents; scalar_t__ ctr_index; int /*<<< orphan*/  ctr_nelems; } ;
struct TYPE_58__ {TYPE_9__ dtu_members; TYPE_7__ dtu_enc; } ;
struct TYPE_57__ {int /*<<< orphan*/  ctt_info; int /*<<< orphan*/  ctt_size; int /*<<< orphan*/  ctt_lsizelo; int /*<<< orphan*/  ctt_lsizehi; } ;
struct TYPE_64__ {scalar_t__ dtd_type; TYPE_2__ dtd_u; TYPE_1__ dtd_data; int /*<<< orphan*/ * dtd_name; } ;
struct TYPE_62__ {int ctf_flags; scalar_t__ ctf_dtoldid; TYPE_8__ ctf_dtdefs; int /*<<< orphan*/  ctf_names; int /*<<< orphan*/  ctf_enums; int /*<<< orphan*/  ctf_unions; int /*<<< orphan*/  ctf_structs; } ;
typedef  TYPE_6__ ctf_file_t ;
typedef  TYPE_7__ ctf_encoding_t ;
typedef  TYPE_8__ ctf_dtdef_t ;
typedef  TYPE_9__ ctf_dmdef_t ;
struct TYPE_56__ {scalar_t__ ctb_type; TYPE_8__* ctb_dtd; TYPE_6__* ctb_file; } ;
typedef  TYPE_10__ ctf_bundle_t ;
typedef  TYPE_7__ ctf_arinfo_t ;

/* Variables and functions */
 int CTF_ADD_ROOT ; 
 scalar_t__ CTF_ERR ; 
 int CTF_INFO_KIND (int /*<<< orphan*/ ) ; 
#define  CTF_K_ARRAY 140 
#define  CTF_K_CONST 139 
#define  CTF_K_ENUM 138 
#define  CTF_K_FLOAT 137 
#define  CTF_K_FORWARD 136 
#define  CTF_K_FUNCTION 135 
#define  CTF_K_INTEGER 134 
#define  CTF_K_POINTER 133 
#define  CTF_K_RESTRICT 132 
#define  CTF_K_STRUCT 131 
#define  CTF_K_TYPEDEF 130 
#define  CTF_K_UNION 129 
 int CTF_K_UNKNOWN ; 
#define  CTF_K_VOLATILE 128 
 int /*<<< orphan*/  CTF_LSIZE_SENT ; 
 int /*<<< orphan*/  CTF_MAX_SIZE ; 
 int /*<<< orphan*/  CTF_SIZE_TO_LSIZE_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_SIZE_TO_LSIZE_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_TYPE_INFO (int,int,int) ; 
 scalar_t__ CTF_TYPE_TO_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  ECTF_CONFLICT ; 
 int /*<<< orphan*/  ECTF_CORRUPT ; 
 int /*<<< orphan*/  ECTF_RDONLY ; 
 int LCTF_INFO_KIND (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int LCTF_INFO_ROOT (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int LCTF_INFO_VLEN (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int LCTF_RDWR ; 
 scalar_t__ bcmp (TYPE_7__*,TYPE_7__*,int) ; 
 scalar_t__ ctf_add_array (TYPE_6__*,int,TYPE_7__*) ; 
 scalar_t__ ctf_add_enum (TYPE_6__*,int,char const*) ; 
 scalar_t__ ctf_add_float (TYPE_6__*,int,char const*,TYPE_7__*) ; 
 scalar_t__ ctf_add_forward (TYPE_6__*,int,char const*,int const) ; 
 scalar_t__ ctf_add_function (TYPE_6__*,int,TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_add_generic (TYPE_6__*,int,char const*,TYPE_8__**) ; 
 scalar_t__ ctf_add_integer (TYPE_6__*,int,char const*,TYPE_7__*) ; 
 scalar_t__ ctf_add_reftype (TYPE_6__*,int,scalar_t__,int) ; 
 scalar_t__ ctf_add_typedef (TYPE_6__*,int,char const*,scalar_t__) ; 
 scalar_t__ ctf_array_info (TYPE_6__*,scalar_t__,TYPE_7__*) ; 
 int /*<<< orphan*/  ctf_enum_iter (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  ctf_errno (TYPE_6__*) ; 
 TYPE_4__* ctf_hash_lookup (int /*<<< orphan*/ *,TYPE_6__*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_9__* ctf_list_next (TYPE_9__*) ; 
 TYPE_8__* ctf_list_prev (TYPE_8__*) ; 
 TYPE_3__* ctf_lookup_by_id (TYPE_6__**,scalar_t__) ; 
 int /*<<< orphan*/  ctf_member_iter (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  ctf_ref_inc (TYPE_6__*,scalar_t__) ; 
 scalar_t__ ctf_set_errno (TYPE_6__*,int /*<<< orphan*/ ) ; 
 char* ctf_strptr (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_type_encoding (TYPE_6__*,scalar_t__,TYPE_7__*) ; 
 int ctf_type_kind (TYPE_6__*,scalar_t__) ; 
 scalar_t__ ctf_type_reference (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  ctf_type_size (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  enumadd ; 
 int /*<<< orphan*/  enumcmp ; 
 int /*<<< orphan*/  membadd ; 
 int /*<<< orphan*/  membcmp ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

ctf_id_t
ctf_add_type(ctf_file_t *dst_fp, ctf_file_t *src_fp, ctf_id_t src_type)
{
	ctf_id_t dst_type = CTF_ERR;
	uint_t dst_kind = CTF_K_UNKNOWN;

	const ctf_type_t *tp;
	const char *name;
	uint_t kind, flag, vlen;

	ctf_bundle_t src, dst;
	ctf_encoding_t src_en, dst_en;
	ctf_arinfo_t src_ar, dst_ar;

	ctf_dtdef_t *dtd;
	ctf_funcinfo_t ctc;
	ssize_t size;

	ctf_hash_t *hp;
	ctf_helem_t *hep;

	if (dst_fp == src_fp)
		return (src_type);

	if (!(dst_fp->ctf_flags & LCTF_RDWR))
		return (ctf_set_errno(dst_fp, ECTF_RDONLY));

	if ((tp = ctf_lookup_by_id(&src_fp, src_type)) == NULL)
		return (ctf_set_errno(dst_fp, ctf_errno(src_fp)));

	name = ctf_strptr(src_fp, tp->ctt_name);
	kind = LCTF_INFO_KIND(src_fp, tp->ctt_info);
	flag = LCTF_INFO_ROOT(src_fp, tp->ctt_info);
	vlen = LCTF_INFO_VLEN(src_fp, tp->ctt_info);

	switch (kind) {
	case CTF_K_STRUCT:
		hp = &dst_fp->ctf_structs;
		break;
	case CTF_K_UNION:
		hp = &dst_fp->ctf_unions;
		break;
	case CTF_K_ENUM:
		hp = &dst_fp->ctf_enums;
		break;
	default:
		hp = &dst_fp->ctf_names;
		break;
	}

	/*
	 * If the source type has a name and is a root type (visible at the
	 * top-level scope), lookup the name in the destination container and
	 * verify that it is of the same kind before we do anything else.
	 */
	if ((flag & CTF_ADD_ROOT) && name[0] != '\0' &&
	    (hep = ctf_hash_lookup(hp, dst_fp, name, strlen(name))) != NULL) {
		dst_type = (ctf_id_t)hep->h_type;
		dst_kind = ctf_type_kind(dst_fp, dst_type);
	}

	/*
	 * If an identically named dst_type exists, fail with ECTF_CONFLICT
	 * unless dst_type is a forward declaration and src_type is a struct,
	 * union, or enum (i.e. the definition of the previous forward decl).
	 */
	if (dst_type != CTF_ERR && dst_kind != kind) {
		if (dst_kind != CTF_K_FORWARD || (kind != CTF_K_ENUM &&
		    kind != CTF_K_STRUCT && kind != CTF_K_UNION))
			return (ctf_set_errno(dst_fp, ECTF_CONFLICT));
		else
			dst_type = CTF_ERR;
	}

	/*
	 * If the non-empty name was not found in the appropriate hash, search
	 * the list of pending dynamic definitions that are not yet committed.
	 * If a matching name and kind are found, assume this is the type that
	 * we are looking for.  This is necessary to permit ctf_add_type() to
	 * operate recursively on entities such as a struct that contains a
	 * pointer member that refers to the same struct type.
	 *
	 * In the case of integer and floating point types, we match using the
	 * type encoding as well - else we may incorrectly return a bitfield
	 * type, for instance.
	 */
	if (dst_type == CTF_ERR && name[0] != '\0') {
		for (dtd = ctf_list_prev(&dst_fp->ctf_dtdefs); dtd != NULL &&
		    CTF_TYPE_TO_INDEX(dtd->dtd_type) > dst_fp->ctf_dtoldid;
		    dtd = ctf_list_prev(dtd)) {
			if (CTF_INFO_KIND(dtd->dtd_data.ctt_info) != kind ||
			    dtd->dtd_name == NULL ||
			    strcmp(dtd->dtd_name, name) != 0)
				continue;
			if (kind == CTF_K_INTEGER || kind == CTF_K_FLOAT) {
				if (ctf_type_encoding(src_fp, src_type,
				    &src_en) != 0)
					continue;
				if (bcmp(&src_en, &dtd->dtd_u.dtu_enc,
				    sizeof (ctf_encoding_t)) != 0)
					continue;
			}
			return (dtd->dtd_type);
		}
	}

	src.ctb_file = src_fp;
	src.ctb_type = src_type;
	src.ctb_dtd = NULL;

	dst.ctb_file = dst_fp;
	dst.ctb_type = dst_type;
	dst.ctb_dtd = NULL;

	/*
	 * Now perform kind-specific processing.  If dst_type is CTF_ERR, then
	 * we add a new type with the same properties as src_type to dst_fp.
	 * If dst_type is not CTF_ERR, then we verify that dst_type has the
	 * same attributes as src_type.  We recurse for embedded references.
	 */
	switch (kind) {
	case CTF_K_INTEGER:
	case CTF_K_FLOAT:
		if (ctf_type_encoding(src_fp, src_type, &src_en) != 0)
			return (ctf_set_errno(dst_fp, ctf_errno(src_fp)));

		if (dst_type != CTF_ERR) {
			if (ctf_type_encoding(dst_fp, dst_type, &dst_en) != 0)
				return (CTF_ERR); /* errno is set for us */

			if (bcmp(&src_en, &dst_en, sizeof (ctf_encoding_t)))
				return (ctf_set_errno(dst_fp, ECTF_CONFLICT));

		} else if (kind == CTF_K_INTEGER) {
			dst_type = ctf_add_integer(dst_fp, flag, name, &src_en);
		} else
			dst_type = ctf_add_float(dst_fp, flag, name, &src_en);
		break;

	case CTF_K_POINTER:
	case CTF_K_VOLATILE:
	case CTF_K_CONST:
	case CTF_K_RESTRICT:
		src_type = ctf_type_reference(src_fp, src_type);
		src_type = ctf_add_type(dst_fp, src_fp, src_type);

		if (src_type == CTF_ERR)
			return (CTF_ERR); /* errno is set for us */

		dst_type = ctf_add_reftype(dst_fp, flag, src_type, kind);
		break;

	case CTF_K_ARRAY:
		if (ctf_array_info(src_fp, src_type, &src_ar) == CTF_ERR)
			return (ctf_set_errno(dst_fp, ctf_errno(src_fp)));

		src_ar.ctr_contents =
		    ctf_add_type(dst_fp, src_fp, src_ar.ctr_contents);
		src_ar.ctr_index =
		    ctf_add_type(dst_fp, src_fp, src_ar.ctr_index);
		src_ar.ctr_nelems = src_ar.ctr_nelems;

		if (src_ar.ctr_contents == CTF_ERR ||
		    src_ar.ctr_index == CTF_ERR)
			return (CTF_ERR); /* errno is set for us */

		if (dst_type != CTF_ERR) {
			if (ctf_array_info(dst_fp, dst_type, &dst_ar) != 0)
				return (CTF_ERR); /* errno is set for us */

			if (bcmp(&src_ar, &dst_ar, sizeof (ctf_arinfo_t)))
				return (ctf_set_errno(dst_fp, ECTF_CONFLICT));
		} else
			dst_type = ctf_add_array(dst_fp, flag, &src_ar);
		break;

	case CTF_K_FUNCTION:
		ctc.ctc_return = ctf_add_type(dst_fp, src_fp, tp->ctt_type);
		ctc.ctc_argc = 0;
		ctc.ctc_flags = 0;

		if (ctc.ctc_return == CTF_ERR)
			return (CTF_ERR); /* errno is set for us */

		dst_type = ctf_add_function(dst_fp, flag, &ctc, NULL);
		break;

	case CTF_K_STRUCT:
	case CTF_K_UNION: {
		ctf_dmdef_t *dmd;
		int errs = 0;

		/*
		 * Technically to match a struct or union we need to check both
		 * ways (src members vs. dst, dst members vs. src) but we make
		 * this more optimal by only checking src vs. dst and comparing
		 * the total size of the structure (which we must do anyway)
		 * which covers the possibility of dst members not in src.
		 * This optimization can be defeated for unions, but is so
		 * pathological as to render it irrelevant for our purposes.
		 */
		if (dst_type != CTF_ERR && dst_kind != CTF_K_FORWARD) {
			if (ctf_type_size(src_fp, src_type) !=
			    ctf_type_size(dst_fp, dst_type))
				return (ctf_set_errno(dst_fp, ECTF_CONFLICT));

			if (ctf_member_iter(src_fp, src_type, membcmp, &dst))
				return (ctf_set_errno(dst_fp, ECTF_CONFLICT));

			break;
		}

		/*
		 * Unlike the other cases, copying structs and unions is done
		 * manually so as to avoid repeated lookups in ctf_add_member
		 * and to ensure the exact same member offsets as in src_type.
		 */
		dst_type = ctf_add_generic(dst_fp, flag, name, &dtd);
		if (dst_type == CTF_ERR)
			return (CTF_ERR); /* errno is set for us */

		dst.ctb_type = dst_type;
		dst.ctb_dtd = dtd;

		if (ctf_member_iter(src_fp, src_type, membadd, &dst) != 0)
			errs++; /* increment errs and fail at bottom of case */

		if ((size = ctf_type_size(src_fp, src_type)) > CTF_MAX_SIZE) {
			dtd->dtd_data.ctt_size = CTF_LSIZE_SENT;
			dtd->dtd_data.ctt_lsizehi = CTF_SIZE_TO_LSIZE_HI(size);
			dtd->dtd_data.ctt_lsizelo = CTF_SIZE_TO_LSIZE_LO(size);
		} else
			dtd->dtd_data.ctt_size = (ushort_t)size;

		dtd->dtd_data.ctt_info = CTF_TYPE_INFO(kind, flag, vlen);

		/*
		 * Make a final pass through the members changing each dmd_type
		 * (a src_fp type) to an equivalent type in dst_fp.  We pass
		 * through all members, leaving any that fail set to CTF_ERR.
		 */
		for (dmd = ctf_list_next(&dtd->dtd_u.dtu_members);
		    dmd != NULL; dmd = ctf_list_next(dmd)) {
			if ((dmd->dmd_type = ctf_add_type(dst_fp, src_fp,
			    dmd->dmd_type)) == CTF_ERR)
				errs++;
		}

		if (errs)
			return (CTF_ERR); /* errno is set for us */

		/*
		 * Now that we know that we can't fail, we go through and bump
		 * all the reference counts on the member types.
		 */
		for (dmd = ctf_list_next(&dtd->dtd_u.dtu_members);
		    dmd != NULL; dmd = ctf_list_next(dmd))
			ctf_ref_inc(dst_fp, dmd->dmd_type);
		break;
	}

	case CTF_K_ENUM:
		if (dst_type != CTF_ERR && dst_kind != CTF_K_FORWARD) {
			if (ctf_enum_iter(src_fp, src_type, enumcmp, &dst) ||
			    ctf_enum_iter(dst_fp, dst_type, enumcmp, &src))
				return (ctf_set_errno(dst_fp, ECTF_CONFLICT));
		} else {
			dst_type = ctf_add_enum(dst_fp, flag, name);
			if ((dst.ctb_type = dst_type) == CTF_ERR ||
			    ctf_enum_iter(src_fp, src_type, enumadd, &dst))
				return (CTF_ERR); /* errno is set for us */
		}
		break;

	case CTF_K_FORWARD:
		if (dst_type == CTF_ERR) {
			dst_type = ctf_add_forward(dst_fp,
			    flag, name, CTF_K_STRUCT); /* assume STRUCT */
		}
		break;

	case CTF_K_TYPEDEF:
		src_type = ctf_type_reference(src_fp, src_type);
		src_type = ctf_add_type(dst_fp, src_fp, src_type);

		if (src_type == CTF_ERR)
			return (CTF_ERR); /* errno is set for us */

		/*
		 * If dst_type is not CTF_ERR at this point, we should check if
		 * ctf_type_reference(dst_fp, dst_type) != src_type and if so
		 * fail with ECTF_CONFLICT.  However, this causes problems with
		 * <sys/types.h> typedefs that vary based on things like if
		 * _ILP32x then pid_t is int otherwise long.  We therefore omit
		 * this check and assume that if the identically named typedef
		 * already exists in dst_fp, it is correct or equivalent.
		 */
		if (dst_type == CTF_ERR) {
			dst_type = ctf_add_typedef(dst_fp, flag,
			    name, src_type);
		}
		break;

	default:
		return (ctf_set_errno(dst_fp, ECTF_CORRUPT));
	}

	return (dst_type);
}
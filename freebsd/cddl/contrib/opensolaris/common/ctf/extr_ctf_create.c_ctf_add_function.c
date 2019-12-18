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
typedef  scalar_t__ ushort_t ;
typedef  int uint_t ;
typedef  scalar_t__ ctf_id_t ;
struct TYPE_9__ {int ctc_flags; int ctc_argc; scalar_t__ const ctc_return; } ;
typedef  TYPE_3__ ctf_funcinfo_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_8__ {scalar_t__* dtu_argv; } ;
struct TYPE_7__ {scalar_t__ ctt_type; int /*<<< orphan*/  ctt_info; } ;
struct TYPE_10__ {TYPE_2__ dtd_u; TYPE_1__ dtd_data; } ;
typedef  TYPE_4__ ctf_dtdef_t ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 int CTF_FUNC_VARARG ; 
 int /*<<< orphan*/  CTF_K_FUNCTION ; 
 int CTF_MAX_VLEN ; 
 int /*<<< orphan*/  CTF_TYPE_INFO (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ECTF_BADID ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  bcopy (scalar_t__ const*,scalar_t__*,int) ; 
 scalar_t__ ctf_add_generic (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_4__**) ; 
 scalar_t__* ctf_alloc (int) ; 
 int /*<<< orphan*/ * ctf_dtd_lookup (int /*<<< orphan*/ *,scalar_t__ const) ; 
 int /*<<< orphan*/  ctf_free (scalar_t__*,int) ; 
 int /*<<< orphan*/ * ctf_lookup_by_id (int /*<<< orphan*/ **,scalar_t__ const) ; 
 int /*<<< orphan*/  ctf_ref_inc (int /*<<< orphan*/ *,scalar_t__ const) ; 
 scalar_t__ ctf_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ctf_id_t
ctf_add_function(ctf_file_t *fp, uint_t flag,
    const ctf_funcinfo_t *ctc, const ctf_id_t *argv)
{
	ctf_dtdef_t *dtd;
	ctf_id_t type;
	uint_t vlen;
	int i;
	ctf_id_t *vdat = NULL;
	ctf_file_t *fpd;

	if (ctc == NULL || (ctc->ctc_flags & ~CTF_FUNC_VARARG) != 0 ||
	    (ctc->ctc_argc != 0 && argv == NULL))
		return (ctf_set_errno(fp, EINVAL));

	vlen = ctc->ctc_argc;
	if (ctc->ctc_flags & CTF_FUNC_VARARG)
		vlen++; /* add trailing zero to indicate varargs (see below) */

	if (vlen > CTF_MAX_VLEN)
		return (ctf_set_errno(fp, EOVERFLOW));

	fpd = fp;
	if (ctf_lookup_by_id(&fpd, ctc->ctc_return) == NULL &&
	    ctf_dtd_lookup(fp, ctc->ctc_return) == NULL)
		return (ctf_set_errno(fp, ECTF_BADID));

	for (i = 0; i < ctc->ctc_argc; i++) {
		fpd = fp;
		if (ctf_lookup_by_id(&fpd, argv[i]) == NULL &&
		    ctf_dtd_lookup(fp, argv[i]) == NULL)
			return (ctf_set_errno(fp, ECTF_BADID));
	}

	if (vlen != 0 && (vdat = ctf_alloc(sizeof (ctf_id_t) * vlen)) == NULL)
		return (ctf_set_errno(fp, EAGAIN));

	if ((type = ctf_add_generic(fp, flag, NULL, &dtd)) == CTF_ERR) {
		ctf_free(vdat, sizeof (ctf_id_t) * vlen);
		return (CTF_ERR); /* errno is set for us */
	}

	dtd->dtd_data.ctt_info = CTF_TYPE_INFO(CTF_K_FUNCTION, flag, vlen);
	dtd->dtd_data.ctt_type = (ushort_t)ctc->ctc_return;

	ctf_ref_inc(fp, ctc->ctc_return);
	for (i = 0; i < ctc->ctc_argc; i++)
		ctf_ref_inc(fp, argv[i]);

	bcopy(argv, vdat, sizeof (ctf_id_t) * ctc->ctc_argc);
	if (ctc->ctc_flags & CTF_FUNC_VARARG)
		vdat[vlen - 1] = 0; /* add trailing zero to indicate varargs */
	dtd->dtd_u.dtu_argv = vdat;

	return (type);
}
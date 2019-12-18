#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_18__ {int ctf_flags; int /*<<< orphan*/  ctf_dtstrlen; } ;
typedef  TYPE_3__ ctf_file_t ;
struct TYPE_20__ {char* dmd_name; int dmd_value; scalar_t__ dmd_offset; int /*<<< orphan*/  dmd_type; } ;
struct TYPE_17__ {TYPE_5__ dtu_members; } ;
struct TYPE_16__ {int /*<<< orphan*/  ctt_info; } ;
struct TYPE_19__ {TYPE_2__ dtd_u; TYPE_1__ dtd_data; } ;
typedef  TYPE_4__ ctf_dtdef_t ;
typedef  TYPE_5__ ctf_dmdef_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 scalar_t__ CTF_INFO_ISROOT (int /*<<< orphan*/ ) ; 
 scalar_t__ CTF_INFO_KIND (int /*<<< orphan*/ ) ; 
 scalar_t__ CTF_INFO_VLEN (int /*<<< orphan*/ ) ; 
 scalar_t__ CTF_K_ENUM ; 
 scalar_t__ CTF_MAX_VLEN ; 
 int /*<<< orphan*/  CTF_TYPE_INFO (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ECTF_BADID ; 
 int /*<<< orphan*/  ECTF_DTFULL ; 
 int /*<<< orphan*/  ECTF_DUPMEMBER ; 
 int /*<<< orphan*/  ECTF_NOTENUM ; 
 int /*<<< orphan*/  ECTF_RDONLY ; 
 int /*<<< orphan*/  EINVAL ; 
 int LCTF_DIRTY ; 
 int LCTF_RDWR ; 
 TYPE_5__* ctf_alloc (int) ; 
 TYPE_4__* ctf_dtd_lookup (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_free (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ctf_list_append (TYPE_5__*,TYPE_5__*) ; 
 TYPE_5__* ctf_list_next (TYPE_5__*) ; 
 int ctf_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 
 char* ctf_strdup (char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ strlen (char*) ; 

int
ctf_add_enumerator(ctf_file_t *fp, ctf_id_t enid, const char *name, int value)
{
	ctf_dtdef_t *dtd = ctf_dtd_lookup(fp, enid);
	ctf_dmdef_t *dmd;

	uint_t kind, vlen, root;
	char *s;

	if (name == NULL)
		return (ctf_set_errno(fp, EINVAL));

	if (!(fp->ctf_flags & LCTF_RDWR))
		return (ctf_set_errno(fp, ECTF_RDONLY));

	if (dtd == NULL)
		return (ctf_set_errno(fp, ECTF_BADID));

	kind = CTF_INFO_KIND(dtd->dtd_data.ctt_info);
	root = CTF_INFO_ISROOT(dtd->dtd_data.ctt_info);
	vlen = CTF_INFO_VLEN(dtd->dtd_data.ctt_info);

	if (kind != CTF_K_ENUM)
		return (ctf_set_errno(fp, ECTF_NOTENUM));

	if (vlen == CTF_MAX_VLEN)
		return (ctf_set_errno(fp, ECTF_DTFULL));

	for (dmd = ctf_list_next(&dtd->dtd_u.dtu_members);
	    dmd != NULL; dmd = ctf_list_next(dmd)) {
		if (strcmp(dmd->dmd_name, name) == 0)
			return (ctf_set_errno(fp, ECTF_DUPMEMBER));
	}

	if ((dmd = ctf_alloc(sizeof (ctf_dmdef_t))) == NULL)
		return (ctf_set_errno(fp, EAGAIN));

	if ((s = ctf_strdup(name)) == NULL) {
		ctf_free(dmd, sizeof (ctf_dmdef_t));
		return (ctf_set_errno(fp, EAGAIN));
	}

	dmd->dmd_name = s;
	dmd->dmd_type = CTF_ERR;
	dmd->dmd_offset = 0;
	dmd->dmd_value = value;

	dtd->dtd_data.ctt_info = CTF_TYPE_INFO(kind, root, vlen + 1);
	ctf_list_append(&dtd->dtd_u.dtu_members, dmd);

	fp->ctf_dtstrlen += strlen(s) + 1;
	fp->ctf_flags |= LCTF_DIRTY;

	return (0);
}
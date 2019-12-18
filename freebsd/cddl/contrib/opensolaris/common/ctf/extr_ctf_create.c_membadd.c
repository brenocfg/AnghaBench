#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_11__ {char* dmd_name; int dmd_value; int /*<<< orphan*/  dmd_offset; int /*<<< orphan*/  dmd_type; } ;
typedef  TYPE_3__ ctf_dmdef_t ;
struct TYPE_12__ {TYPE_5__* ctb_file; TYPE_2__* ctb_dtd; } ;
typedef  TYPE_4__ ctf_bundle_t ;
struct TYPE_13__ {int /*<<< orphan*/  ctf_flags; int /*<<< orphan*/  ctf_dtstrlen; } ;
struct TYPE_9__ {int /*<<< orphan*/  dtu_members; } ;
struct TYPE_10__ {TYPE_1__ dtd_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  LCTF_DIRTY ; 
 TYPE_3__* ctf_alloc (int) ; 
 int /*<<< orphan*/  ctf_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ctf_list_append (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int ctf_set_errno (TYPE_5__*,int /*<<< orphan*/ ) ; 
 char* ctf_strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
membadd(const char *name, ctf_id_t type, ulong_t offset, void *arg)
{
	ctf_bundle_t *ctb = arg;
	ctf_dmdef_t *dmd;
	char *s = NULL;

	if ((dmd = ctf_alloc(sizeof (ctf_dmdef_t))) == NULL)
		return (ctf_set_errno(ctb->ctb_file, EAGAIN));

	if (name != NULL && (s = ctf_strdup(name)) == NULL) {
		ctf_free(dmd, sizeof (ctf_dmdef_t));
		return (ctf_set_errno(ctb->ctb_file, EAGAIN));
	}

	/*
	 * For now, dmd_type is copied as the src_fp's type; it is reset to an
	 * equivalent dst_fp type by a final loop in ctf_add_type(), below.
	 */
	dmd->dmd_name = s;
	dmd->dmd_type = type;
	dmd->dmd_offset = offset;
	dmd->dmd_value = -1;

	ctf_list_append(&ctb->ctb_dtd->dtd_u.dtu_members, dmd);

	if (s != NULL)
		ctb->ctb_file->ctf_dtstrlen += strlen(s) + 1;

	ctb->ctb_file->ctf_flags |= LCTF_DIRTY;
	return (0);
}
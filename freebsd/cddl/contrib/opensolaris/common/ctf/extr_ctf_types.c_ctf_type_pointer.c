#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_6__ {int ctf_flags; int /*<<< orphan*/ * ctf_ptrtab; } ;
typedef  TYPE_1__ ctf_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  CTF_INDEX_TO_TYPE (int /*<<< orphan*/ ,int) ; 
 size_t CTF_TYPE_TO_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECTF_NOTYPE ; 
 int LCTF_CHILD ; 
 int /*<<< orphan*/ * ctf_lookup_by_id (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (TYPE_1__*,int /*<<< orphan*/ ) ; 

ctf_id_t
ctf_type_pointer(ctf_file_t *fp, ctf_id_t type)
{
	ctf_file_t *ofp = fp;
	ctf_id_t ntype;

	if (ctf_lookup_by_id(&fp, type) == NULL)
		return (CTF_ERR); /* errno is set for us */

	if ((ntype = fp->ctf_ptrtab[CTF_TYPE_TO_INDEX(type)]) != 0)
		return (CTF_INDEX_TO_TYPE(ntype, (fp->ctf_flags & LCTF_CHILD)));

	if ((type = ctf_type_resolve(fp, type)) == CTF_ERR)
		return (ctf_set_errno(ofp, ECTF_NOTYPE));

	if (ctf_lookup_by_id(&fp, type) == NULL)
		return (ctf_set_errno(ofp, ECTF_NOTYPE));

	if ((ntype = fp->ctf_ptrtab[CTF_TYPE_TO_INDEX(type)]) != 0)
		return (CTF_INDEX_TO_TYPE(ntype, (fp->ctf_flags & LCTF_CHILD)));

	return (ctf_set_errno(ofp, ECTF_NOTYPE));
}
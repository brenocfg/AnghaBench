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
struct TYPE_6__ {scalar_t__ ctf_refcnt; scalar_t__ ctf_dmodel; struct TYPE_6__* ctf_parent; int /*<<< orphan*/  ctf_flags; } ;
typedef  TYPE_1__ ctf_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECTF_DMODEL ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LCTF_CHILD ; 
 int /*<<< orphan*/  ctf_close (TYPE_1__*) ; 
 int ctf_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
ctf_import(ctf_file_t *fp, ctf_file_t *pfp)
{
	if (fp == NULL || fp == pfp || (pfp != NULL && pfp->ctf_refcnt == 0))
		return (ctf_set_errno(fp, EINVAL));

	if (pfp != NULL && pfp->ctf_dmodel != fp->ctf_dmodel)
		return (ctf_set_errno(fp, ECTF_DMODEL));

	if (fp->ctf_parent != NULL)
		ctf_close(fp->ctf_parent);

	if (pfp != NULL) {
		fp->ctf_flags |= LCTF_CHILD;
		pfp->ctf_refcnt++;
	}

	fp->ctf_parent = pfp;
	return (0);
}
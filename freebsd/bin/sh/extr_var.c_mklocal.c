#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct var {int flags; size_t name_len; int /*<<< orphan*/ * text; } ;
struct localvar {int flags; struct localvar* next; struct var* vp; int /*<<< orphan*/ * text; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int VNOLOCAL ; 
 int VSTRFIXED ; 
 int VTEXTFIXED ; 
 int VUNSET ; 
 void* ckmalloc (int) ; 
 struct var* find_var (char*,struct var***,int /*<<< orphan*/ *) ; 
 struct localvar* localvars ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optval ; 
 int /*<<< orphan*/  savestr (char*) ; 
 int /*<<< orphan*/  setvar (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setvareq (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strchr (char*,char) ; 

void
mklocal(char *name)
{
	struct localvar *lvp;
	struct var **vpp;
	struct var *vp;

	INTOFF;
	lvp = ckmalloc(sizeof (struct localvar));
	if (name[0] == '-' && name[1] == '\0') {
		lvp->text = ckmalloc(sizeof optval);
		memcpy(lvp->text, optval, sizeof optval);
		vp = NULL;
	} else {
		vp = find_var(name, &vpp, NULL);
		if (vp == NULL) {
			if (strchr(name, '='))
				setvareq(savestr(name), VSTRFIXED | VNOLOCAL);
			else
				setvar(name, NULL, VSTRFIXED | VNOLOCAL);
			vp = *vpp;	/* the new variable */
			lvp->text = NULL;
			lvp->flags = VUNSET;
		} else {
			lvp->text = vp->text;
			lvp->flags = vp->flags;
			vp->flags |= VSTRFIXED|VTEXTFIXED;
			if (name[vp->name_len] == '=')
				setvareq(savestr(name), VNOLOCAL);
		}
	}
	lvp->vp = vp;
	lvp->next = localvars;
	localvars = lvp;
	INTON;
}
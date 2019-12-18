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
struct var {int flags; int name_len; char* text; int /*<<< orphan*/  (* func ) (char*) ;struct var* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  LC_ALL ; 
 int VEXPORT ; 
 int VNOFUNC ; 
 int VNOLOCAL ; 
 int VNOSET ; 
 int VREADONLY ; 
 int VSTACK ; 
 int VTEXTFIXED ; 
 int VUNSET ; 
 scalar_t__ aflag ; 
 int /*<<< orphan*/  change_env (char*,int) ; 
 int /*<<< orphan*/  chkmail (int) ; 
 int /*<<< orphan*/  ckfree (char*) ; 
 struct var* ckmalloc (int) ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 struct var* find_var (char*,struct var***,int*) ; 
 scalar_t__ forcelocal ; 
 int iflag ; 
 scalar_t__ localevar (char*) ; 
 int /*<<< orphan*/  mklocal (char*) ; 
 int /*<<< orphan*/  mpathset () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int /*<<< orphan*/  updatecharset () ; 
 struct var vmail ; 
 struct var vmpath ; 

void
setvareq(char *s, int flags)
{
	struct var *vp, **vpp;
	int nlen;

	if (aflag)
		flags |= VEXPORT;
	if (forcelocal && !(flags & (VNOSET | VNOLOCAL)))
		mklocal(s);
	vp = find_var(s, &vpp, &nlen);
	if (vp != NULL) {
		if (vp->flags & VREADONLY) {
			if ((flags & (VTEXTFIXED|VSTACK)) == 0)
				ckfree(s);
			error("%.*s: is read only", vp->name_len, vp->text);
		}
		if (flags & VNOSET) {
			if ((flags & (VTEXTFIXED|VSTACK)) == 0)
				ckfree(s);
			return;
		}
		INTOFF;

		if (vp->func && (flags & VNOFUNC) == 0)
			(*vp->func)(s + vp->name_len + 1);

		if ((vp->flags & (VTEXTFIXED|VSTACK)) == 0)
			ckfree(vp->text);

		vp->flags &= ~(VTEXTFIXED|VSTACK|VUNSET);
		vp->flags |= flags;
		vp->text = s;

		/*
		 * We could roll this to a function, to handle it as
		 * a regular variable function callback, but why bother?
		 *
		 * Note: this assumes iflag is not set to 1 initially.
		 * As part of initvar(), this is called before arguments
		 * are looked at.
		 */
		if ((vp == &vmpath || (vp == &vmail && ! mpathset())) &&
		    iflag == 1)
			chkmail(1);
		if ((vp->flags & VEXPORT) && localevar(s)) {
			change_env(s, 1);
			(void) setlocale(LC_ALL, "");
			updatecharset();
		}
		INTON;
		return;
	}
	/* not found */
	if (flags & VNOSET) {
		if ((flags & (VTEXTFIXED|VSTACK)) == 0)
			ckfree(s);
		return;
	}
	INTOFF;
	vp = ckmalloc(sizeof (*vp));
	vp->flags = flags;
	vp->text = s;
	vp->name_len = nlen;
	vp->next = *vpp;
	vp->func = NULL;
	*vpp = vp;
	if ((vp->flags & VEXPORT) && localevar(s)) {
		change_env(s, 1);
		(void) setlocale(LC_ALL, "");
		updatecharset();
	}
	INTON;
}
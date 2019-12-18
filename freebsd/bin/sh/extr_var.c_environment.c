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
struct var {int flags; int /*<<< orphan*/  text; struct var* next; } ;

/* Variables and functions */
 int VEXPORT ; 
 int VTABSIZE ; 
 int VUNSET ; 
 char** stalloc (int) ; 
 struct var** vartab ; 

char **
environment(void)
{
	int nenv;
	struct var **vpp;
	struct var *vp;
	char **env, **ep;

	nenv = 0;
	for (vpp = vartab ; vpp < vartab + VTABSIZE ; vpp++) {
		for (vp = *vpp ; vp ; vp = vp->next)
			if ((vp->flags & (VEXPORT|VUNSET)) == VEXPORT)
				nenv++;
	}
	ep = env = stalloc((nenv + 1) * sizeof *env);
	for (vpp = vartab ; vpp < vartab + VTABSIZE ; vpp++) {
		for (vp = *vpp ; vp ; vp = vp->next)
			if ((vp->flags & (VEXPORT|VUNSET)) == VEXPORT)
				*ep++ = vp->text;
	}
	*ep = NULL;
	return env;
}
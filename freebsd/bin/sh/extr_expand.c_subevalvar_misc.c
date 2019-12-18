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
struct nodelist {int dummy; } ;

/* Variables and functions */
 char const CTLENDVAR ; 
 int /*<<< orphan*/  EXP_TILDE ; 
 int /*<<< orphan*/  STACKSTRNUL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STADJUST (int,int /*<<< orphan*/ ) ; 
#define  VSASSIGN 129 
 int VSNUL ; 
#define  VSQUESTION 128 
 int /*<<< orphan*/  abort () ; 
 char* argstr (char const*,struct nodelist**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  expdest ; 
 int /*<<< orphan*/  out2 ; 
 int /*<<< orphan*/  outfmt (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  setvar (char const*,char*,int /*<<< orphan*/ ) ; 
 char* stackblock () ; 

__attribute__((used)) static const char *
subevalvar_misc(const char *p, struct nodelist **restrict argbackq,
    const char *var, int subtype, int startloc, int varflags)
{
	const char *end;
	char *startp;
	int amount;

	end = argstr(p, argbackq, EXP_TILDE, NULL);
	STACKSTRNUL(expdest);
	startp = stackblock() + startloc;

	switch (subtype) {
	case VSASSIGN:
		setvar(var, startp, 0);
		amount = startp - expdest;
		STADJUST(amount, expdest);
		return end;

	case VSQUESTION:
		if (*p != CTLENDVAR) {
			outfmt(out2, "%s\n", startp);
			error((char *)NULL);
		}
		error("%.*s: parameter %snot set", (int)(p - var - 1),
		      var, (varflags & VSNUL) ? "null or " : "");

	default:
		abort();
	}
}
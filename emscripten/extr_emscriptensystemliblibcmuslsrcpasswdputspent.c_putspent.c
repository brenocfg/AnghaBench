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
struct spwd {int /*<<< orphan*/  sp_pwdp; int /*<<< orphan*/  sp_namp; int /*<<< orphan*/  sp_flag; int /*<<< orphan*/  sp_expire; int /*<<< orphan*/  sp_inact; int /*<<< orphan*/  sp_warn; int /*<<< orphan*/  sp_max; int /*<<< orphan*/  sp_min; int /*<<< orphan*/  sp_lstchg; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  NUM (int /*<<< orphan*/ ) ; 
 char* STR (int /*<<< orphan*/ ) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int putspent(const struct spwd *sp, FILE *f)
{
	return fprintf(f, "%s:%s:%.*ld:%.*ld:%.*ld:%.*ld:%.*ld:%.*ld:%.*lu\n",
		STR(sp->sp_namp), STR(sp->sp_pwdp), NUM(sp->sp_lstchg),
		NUM(sp->sp_min), NUM(sp->sp_max), NUM(sp->sp_warn),
		NUM(sp->sp_inact), NUM(sp->sp_expire), NUM(sp->sp_flag)) < 0 ? -1 : 0;
}
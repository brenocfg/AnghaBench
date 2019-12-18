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
struct redirtab {scalar_t__* renamed; scalar_t__ empty_redirs; struct redirtab* next; int /*<<< orphan*/  fd0_redirected; } ;

/* Variables and functions */
 scalar_t__ EMPTY ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  ckfree (struct redirtab*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (scalar_t__,int) ; 
 scalar_t__ empty_redirs ; 
 int /*<<< orphan*/  fd0_redirected ; 
 struct redirtab* redirlist ; 

void
popredir(void)
{
	struct redirtab *rp = redirlist;
	int i;

	INTOFF;
	if (empty_redirs > 0) {
		empty_redirs--;
		INTON;
		return;
	}
	for (i = 0 ; i < 10 ; i++) {
		if (rp->renamed[i] != EMPTY) {
			if (rp->renamed[i] >= 0) {
				dup2(rp->renamed[i], i);
				close(rp->renamed[i]);
			} else {
				close(i);
			}
		}
	}
	fd0_redirected = rp->fd0_redirected;
	empty_redirs = rp->empty_redirs;
	redirlist = rp->next;
	ckfree(rp);
	INTON;
}
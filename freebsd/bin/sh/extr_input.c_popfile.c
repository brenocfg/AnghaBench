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
struct parsefile {scalar_t__ fd; int /*<<< orphan*/  linno; int /*<<< orphan*/  nextc; int /*<<< orphan*/  lleft; int /*<<< orphan*/  nleft; struct parsefile* prev; scalar_t__ strpush; struct parsefile* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  ckfree (struct parsefile*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 struct parsefile* parsefile ; 
 int /*<<< orphan*/  parselleft ; 
 int /*<<< orphan*/  parsenextc ; 
 int /*<<< orphan*/  parsenleft ; 
 int /*<<< orphan*/  plinno ; 
 int /*<<< orphan*/  popstring () ; 

void
popfile(void)
{
	struct parsefile *pf = parsefile;

	INTOFF;
	if (pf->fd >= 0)
		close(pf->fd);
	if (pf->buf)
		ckfree(pf->buf);
	while (pf->strpush)
		popstring();
	parsefile = pf->prev;
	ckfree(pf);
	parsenleft = parsefile->nleft;
	parselleft = parsefile->lleft;
	parsenextc = parsefile->nextc;
	plinno = parsefile->linno;
	INTON;
}
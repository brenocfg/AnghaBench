#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * prev; } ;
struct parsefile {int fd; TYPE_1__ basestrpush; int /*<<< orphan*/ * strpush; struct parsefile* prev; int /*<<< orphan*/  linno; int /*<<< orphan*/  nextc; int /*<<< orphan*/  lleft; int /*<<< orphan*/  nleft; } ;

/* Variables and functions */
 scalar_t__ ckmalloc (int) ; 
 struct parsefile* parsefile ; 
 int /*<<< orphan*/  parselleft ; 
 int /*<<< orphan*/  parsenextc ; 
 int /*<<< orphan*/  parsenleft ; 
 int /*<<< orphan*/  plinno ; 

__attribute__((used)) static void
pushfile(void)
{
	struct parsefile *pf;

	parsefile->nleft = parsenleft;
	parsefile->lleft = parselleft;
	parsefile->nextc = parsenextc;
	parsefile->linno = plinno;
	pf = (struct parsefile *)ckmalloc(sizeof (struct parsefile));
	pf->prev = parsefile;
	pf->fd = -1;
	pf->strpush = NULL;
	pf->basestrpush.prev = NULL;
	parsefile = pf;
}
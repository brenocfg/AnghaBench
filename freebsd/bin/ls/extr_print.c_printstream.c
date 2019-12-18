#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  s_block; int /*<<< orphan*/  s_inode; TYPE_1__* list; } ;
struct TYPE_5__ {scalar_t__ fts_number; struct TYPE_5__* fts_link; int /*<<< orphan*/  fts_name; } ;
typedef  TYPE_1__ FTSENT ;
typedef  TYPE_2__ DISPLAY ;

/* Variables and functions */
 scalar_t__ NO_PRINT ; 
 scalar_t__ printaname (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ termwidth ; 

void
printstream(const DISPLAY *dp)
{
	FTSENT *p;
	int chcnt;

	for (p = dp->list, chcnt = 0; p; p = p->fts_link) {
		if (p->fts_number == NO_PRINT)
			continue;
		/* XXX strlen does not take octal escapes into account. */
		if (strlen(p->fts_name) + chcnt +
		    (p->fts_link ? 2 : 0) >= (unsigned)termwidth) {
			putchar('\n');
			chcnt = 0;
		}
		chcnt += printaname(p, dp->s_inode, dp->s_block);
		if (p->fts_link) {
			printf(", ");
			chcnt += 2;
		}
	}
	if (chcnt)
		putchar('\n');
}
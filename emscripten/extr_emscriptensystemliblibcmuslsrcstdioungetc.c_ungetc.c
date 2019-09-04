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
struct TYPE_6__ {int* rpos; int* buf; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  F_EOF ; 
 int* UNGET ; 
 int /*<<< orphan*/  __toread (TYPE_1__*) ; 

int ungetc(int c, FILE *f)
{
	if (c == EOF) return c;

	FLOCK(f);

	if (!f->rpos) __toread(f);
	if (!f->rpos || f->rpos <= f->buf - UNGET) {
		FUNLOCK(f);
		return EOF;
	}

	*--f->rpos = c;
	f->flags &= ~F_EOF;

	FUNLOCK(f);
	return c;
}
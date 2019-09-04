#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_4__ {scalar_t__ (* seek ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int flags; scalar_t__ wpos; scalar_t__ wbase; scalar_t__ rend; scalar_t__ rpos; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int F_APP ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

off_t __ftello_unlocked(FILE *f)
{
	off_t pos = f->seek(f, 0,
		(f->flags & F_APP) && f->wpos > f->wbase
		? SEEK_END : SEEK_CUR);
	if (pos < 0) return pos;

	/* Adjust for data in buffer. */
	return pos - (f->rend - f->rpos) + (f->wpos - f->wbase);
}
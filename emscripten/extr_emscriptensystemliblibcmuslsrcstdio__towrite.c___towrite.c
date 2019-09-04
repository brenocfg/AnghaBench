#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; int flags; scalar_t__ buf_size; scalar_t__ buf; scalar_t__ wend; scalar_t__ wbase; scalar_t__ wpos; scalar_t__ rend; scalar_t__ rpos; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int EOF ; 
 int F_ERR ; 
 int F_NOWR ; 

int __towrite(FILE *f)
{
	f->mode |= f->mode-1;
	if (f->flags & (F_NOWR)) {
		f->flags |= F_ERR;
		return EOF;
	}
	/* Clear read buffer (easier than summoning nasal demons) */
	f->rpos = f->rend = 0;

	/* Activate write through the buffer. */
	f->wpos = f->wbase = f->buf;
	f->wend = f->buf + f->buf_size;

	return 0;
}
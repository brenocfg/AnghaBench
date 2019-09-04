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
struct TYPE_4__ {int mode; scalar_t__ wpos; scalar_t__ wbase; scalar_t__ wend; int flags; scalar_t__ buf_size; scalar_t__ buf; scalar_t__ rend; scalar_t__ rpos; int /*<<< orphan*/  (* write ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int EOF ; 
 int F_EOF ; 
 int F_ERR ; 
 int F_NORD ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __toread(FILE *f)
{
	f->mode |= f->mode-1;
	if (f->wpos > f->wbase) f->write(f, 0, 0);
	f->wpos = f->wbase = f->wend = 0;
	if (f->flags & F_NORD) {
		f->flags |= F_ERR;
		return EOF;
	}
	f->rpos = f->rend = f->buf + f->buf_size;
	return (f->flags & F_EOF) ? EOF : 0;
}
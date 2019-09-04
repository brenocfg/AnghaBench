#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_5__ {scalar_t__ wpos; scalar_t__ wbase; scalar_t__ wend; scalar_t__ (* seek ) (TYPE_1__*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  flags; scalar_t__ rend; scalar_t__ rpos; int /*<<< orphan*/  (* write ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_EOF ; 
 int SEEK_CUR ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int __fseeko_unlocked(FILE *f, off_t off, int whence)
{
	/* Adjust relative offset for unread data in buffer, if any. */
	if (whence == SEEK_CUR) off -= f->rend - f->rpos;

	/* Flush write buffer, and report error on failure. */
	if (f->wpos > f->wbase) {
		f->write(f, 0, 0);
		if (!f->wpos) return -1;
	}

	/* Leave writing mode */
	f->wpos = f->wbase = f->wend = 0;

	/* Perform the underlying seek. */
	if (f->seek(f, off, whence) < 0) return -1;

	/* If seek succeeded, file is seekable and we discard read buffer. */
	f->rpos = f->rend = 0;
	f->flags &= ~F_EOF;
	
	return 0;
}
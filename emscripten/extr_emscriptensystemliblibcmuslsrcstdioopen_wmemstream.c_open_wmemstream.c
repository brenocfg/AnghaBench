#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
struct cookie {size_t* sizep; size_t pos; size_t len; size_t space; scalar_t__* buf; scalar_t__** bufp; } ;
struct TYPE_9__ {int /*<<< orphan*/  threaded; } ;
struct TYPE_8__ {int fd; int lock; int /*<<< orphan*/  close; int /*<<< orphan*/  seek; int /*<<< orphan*/  write; int /*<<< orphan*/  lbf; scalar_t__ buf_size; void* buf; int /*<<< orphan*/  flags; struct cookie* cookie; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EOF ; 
 int /*<<< orphan*/  F_NORD ; 
 TYPE_1__* __ofl_add (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_4__ libc ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wms_close ; 
 int /*<<< orphan*/  wms_seek ; 
 int /*<<< orphan*/  wms_write ; 

FILE *open_wmemstream(wchar_t **bufp, size_t *sizep)
{
	FILE *f;
	struct cookie *c;
	wchar_t *buf;

	if (!(f=malloc(sizeof *f + sizeof *c))) return 0;
	if (!(buf=malloc(sizeof *buf))) {
		free(f);
		return 0;
	}
	memset(f, 0, sizeof *f + sizeof *c);
	f->cookie = c = (void *)(f+1);

	c->bufp = bufp;
	c->sizep = sizep;
	c->pos = c->len = c->space = *sizep = 0;
	c->buf = *bufp = buf;
	*buf = 0;

	f->flags = F_NORD;
	f->fd = -1;
	f->buf = (void *)(c+1);
	f->buf_size = 0;
	f->lbf = EOF;
	f->write = wms_write;
	f->seek = wms_seek;
	f->close = wms_close;

	if (!libc.threaded) f->lock = -1;

	return __ofl_add(f);
}
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
struct cookie {char** bufp; size_t* sizep; size_t pos; size_t len; size_t space; char* buf; } ;
struct TYPE_9__ {int /*<<< orphan*/  threaded; } ;
struct TYPE_8__ {int fd; int buf_size; int lock; int /*<<< orphan*/  close; int /*<<< orphan*/  seek; int /*<<< orphan*/  write; int /*<<< orphan*/  lbf; void* buf; int /*<<< orphan*/  flags; struct cookie* cookie; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  EOF ; 
 int /*<<< orphan*/  F_NORD ; 
 TYPE_1__* __ofl_add (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_4__ libc ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ms_close ; 
 int /*<<< orphan*/  ms_seek ; 
 int /*<<< orphan*/  ms_write ; 

FILE *open_memstream(char **bufp, size_t *sizep)
{
	FILE *f;
	struct cookie *c;
	char *buf;

	if (!(f=malloc(sizeof *f + sizeof *c + BUFSIZ))) return 0;
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
	f->buf_size = BUFSIZ;
	f->lbf = EOF;
	f->write = ms_write;
	f->seek = ms_seek;
	f->close = ms_close;

	if (!libc.threaded) f->lock = -1;

	return __ofl_add(f);
}
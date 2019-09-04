#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct cookie {size_t size; char mode; size_t len; size_t pos; void* buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  threaded; } ;
struct TYPE_7__ {int fd; unsigned char* buf; int buf_size; int lock; int /*<<< orphan*/  close; int /*<<< orphan*/  seek; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  flags; int /*<<< orphan*/  lbf; struct cookie* cookie; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOF ; 
 int /*<<< orphan*/  F_NORD ; 
 int /*<<< orphan*/  F_NOWR ; 
 int SIZE_MAX ; 
 int UNGET ; 
 TYPE_1__* __ofl_add (TYPE_1__*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_2__ libc ; 
 int /*<<< orphan*/  mclose ; 
 int /*<<< orphan*/  mread ; 
 int /*<<< orphan*/  mseek ; 
 int /*<<< orphan*/  mwrite ; 
 int /*<<< orphan*/  strchr (char const*,char const) ; 
 size_t strnlen (void*,size_t) ; 

FILE *fmemopen(void *restrict buf, size_t size, const char *restrict mode)
{
	FILE *f;
	struct cookie *c;
	int plus = !!strchr(mode, '+');
	
	if (!size || !strchr("rwa", *mode)) {
		errno = EINVAL;
		return 0;
	}

	if (!buf && size > SIZE_MAX-sizeof(FILE)-BUFSIZ-UNGET) {
		errno = ENOMEM;
		return 0;
	}

	f = calloc(sizeof *f + sizeof *c + UNGET + BUFSIZ + (buf?0:size), 1);
	if (!f) return 0;
	f->cookie = c = (void *)(f+1);
	f->fd = -1;
	f->lbf = EOF;
	f->buf = (unsigned char *)(c+1) + UNGET;
	f->buf_size = BUFSIZ;
	if (!buf) buf = f->buf + BUFSIZ;

	c->buf = buf;
	c->size = size;
	c->mode = *mode;
	
	if (!plus) f->flags = (*mode == 'r') ? F_NOWR : F_NORD;
	if (*mode == 'r') c->len = size;
	else if (*mode == 'a') c->len = c->pos = strnlen(buf, size);

	f->read = mread;
	f->write = mwrite;
	f->seek = mseek;
	f->close = mclose;

	if (!libc.threaded) f->lock = -1;

	return __ofl_add(f);
}
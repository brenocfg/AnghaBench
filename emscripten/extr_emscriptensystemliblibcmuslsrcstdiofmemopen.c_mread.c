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
struct cookie {size_t len; size_t pos; scalar_t__ buf; } ;
struct TYPE_3__ {size_t buf_size; unsigned char* rpos; unsigned char* buf; unsigned char* rend; int /*<<< orphan*/  flags; struct cookie* cookie; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_EOF ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,size_t) ; 

__attribute__((used)) static size_t mread(FILE *f, unsigned char *buf, size_t len)
{
	struct cookie *c = f->cookie;
	size_t rem = c->len - c->pos;
	if (c->pos > c->len) rem = 0;
	if (len > rem) {
		len = rem;
		f->flags |= F_EOF;
	}
	memcpy(buf, c->buf+c->pos, len);
	c->pos += len;
	rem -= len;
	if (rem > f->buf_size) rem = f->buf_size;
	f->rpos = f->buf;
	f->rend = f->buf + rem;
	memcpy(f->rpos, c->buf+c->pos, rem);
	c->pos += rem;
	return len;
}
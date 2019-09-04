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
typedef  int /*<<< orphan*/  wchar_t ;
struct cookie {size_t pos; size_t space; size_t len; size_t* sizep; int /*<<< orphan*/  mbs; int /*<<< orphan*/ * buf; int /*<<< orphan*/ ** bufp; } ;
struct TYPE_3__ {struct cookie* cookie; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int SSIZE_MAX ; 
 size_t mbsnrtowcs (int /*<<< orphan*/ *,void*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static size_t wms_write(FILE *f, const unsigned char *buf, size_t len)
{
	struct cookie *c = f->cookie;
	size_t len2;
	wchar_t *newbuf;
	if (len + c->pos >= c->space) {
		len2 = 2*c->space+1 | c->pos+len+1;
		if (len2 > SSIZE_MAX/4) return 0;
		newbuf = realloc(c->buf, len2*4);
		if (!newbuf) return 0;
		*c->bufp = c->buf = newbuf;
		memset(c->buf + c->space, 0, 4*(len2 - c->space));
		c->space = len2;
	}
	
	len2 = mbsnrtowcs(c->buf+c->pos, (void *)&buf, len, c->space-c->pos, &c->mbs);
	if (len2 == -1) return 0;
	c->pos += len2;
	if (c->pos >= c->len) c->len = c->pos;
	*c->sizep = c->pos;
	return len;
}
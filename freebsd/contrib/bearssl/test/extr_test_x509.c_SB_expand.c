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
struct TYPE_3__ {size_t len; size_t ptr; char* buf; } ;
typedef  TYPE_1__ string_builder ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static void
SB_expand(string_builder *sb, size_t extra_len)
{
	size_t nlen;
	char *nbuf;

	if (extra_len < (sb->len - sb->ptr)) {
		return;
	}
	nlen = sb->len << 1;
	if (extra_len > (nlen - sb->ptr)) {
		nlen = sb->ptr + extra_len;
	}
	nbuf = xmalloc(nlen);
	memcpy(nbuf, sb->buf, sb->ptr);
	xfree(sb->buf);
	sb->buf = nbuf;
	sb->len = nlen;
}
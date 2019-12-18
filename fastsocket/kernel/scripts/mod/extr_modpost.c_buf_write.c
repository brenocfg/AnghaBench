#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct buffer {int size; int pos; int p; } ;

/* Variables and functions */
 int SZ ; 
 int realloc (int,int) ; 
 int /*<<< orphan*/  strncpy (int,char const*,int) ; 

void buf_write(struct buffer *buf, const char *s, int len)
{
	if (buf->size - buf->pos < len) {
		buf->size += len + SZ;
		buf->p = realloc(buf->p, buf->size);
	}
	strncpy(buf->p + buf->pos, s, len);
	buf->pos += len;
}
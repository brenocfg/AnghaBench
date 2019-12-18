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
struct Buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct Buf* buf_strappend (struct Buf*,char*) ; 
 char* flex_alloc (size_t) ; 
 int /*<<< orphan*/  flex_free (char*) ; 
 int /*<<< orphan*/  flexfatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char const*,char const*) ; 
 int strlen (char const*) ; 

struct Buf *buf_prints (struct Buf *buf, const char *fmt, const char *s)
{
	char   *t;
        size_t tsz;

	t = flex_alloc (tsz = strlen (fmt) + strlen (s) + 1);
	if (!t)
	    flexfatal (_("Allocation of buffer to print string failed"));
	snprintf (t, tsz, fmt, s);
	buf = buf_strappend (buf, t);
	flex_free (t);
	return buf;
}
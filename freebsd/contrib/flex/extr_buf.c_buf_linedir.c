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
 int NUMCHARLINES ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct Buf* buf_strappend (struct Buf*,char*) ; 
 char* flex_alloc (int) ; 
 int /*<<< orphan*/  flex_free (char*) ; 
 int /*<<< orphan*/  flexfatal (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int) ; 
 int strlen (char const*) ; 

struct Buf *buf_linedir (struct Buf *buf, const char* filename, int lineno)
{
    char *dst, *t;
    const char *src;

    t = flex_alloc (strlen ("#line \"\"\n")          +   /* constant parts */
                    2 * strlen (filename)            +   /* filename with possibly all backslashes escaped */
                    NUMCHARLINES                     +   /* line number */
                    1);                                  /* NUL */
    if (!t)
      flexfatal (_("Allocation of buffer for line directive failed"));
    for (dst = t + sprintf (t, "#line %d \"", lineno), src = filename; *src; *dst++ = *src++)
      if (*src == '\\')   /* escape backslashes */
        *dst++ = '\\';
    *dst++ = '"';
    *dst++ = '\n';
    *dst   = '\0';
    buf = buf_strappend (buf, t);
    flex_free (t);
    return buf;
}
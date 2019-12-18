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
 int /*<<< orphan*/  buf_append (struct Buf*,char**,int) ; 
 scalar_t__ flex_alloc (size_t) ; 
 int /*<<< orphan*/  flexfatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char const*,char const*,char const*) ; 
 int strlen (char const*) ; 

struct Buf *buf_m4_define (struct Buf *buf, const char* def, const char* val)
{
    const char * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    char * str;
    size_t strsz;

    val = val?val:"";
    str = (char*)flex_alloc(strsz = strlen(fmt) + strlen(def) + strlen(val) + 2);
    if (!str)
        flexfatal (_("Allocation of buffer for m4 def failed"));

    snprintf(str, strsz, fmt, def, val);
    buf_append(buf, &str, 1);
    return buf;
}
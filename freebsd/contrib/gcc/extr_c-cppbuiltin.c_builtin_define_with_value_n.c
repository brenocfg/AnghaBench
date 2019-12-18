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

/* Variables and functions */
 scalar_t__ alloca (size_t) ; 
 int /*<<< orphan*/  cpp_define (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  parse_in ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
builtin_define_with_value_n (const char *macro, const char *expansion, size_t elen)
{
  char *buf;
  size_t mlen = strlen (macro);

  /* Space for an = and a NUL.  */
  buf = (char *) alloca (mlen + elen + 2);
  memcpy (buf, macro, mlen);
  buf[mlen] = '=';
  memcpy (buf + mlen + 1, expansion, elen);
  buf[mlen + elen + 1] = '\0';

  cpp_define (parse_in, buf);
}
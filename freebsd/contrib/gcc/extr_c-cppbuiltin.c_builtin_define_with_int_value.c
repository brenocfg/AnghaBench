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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 char* HOST_WIDE_INT_PRINT_DEC ; 
 scalar_t__ alloca (size_t) ; 
 int /*<<< orphan*/  cpp_define (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  parse_in ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
builtin_define_with_int_value (const char *macro, HOST_WIDE_INT value)
{
  char *buf;
  size_t mlen = strlen (macro);
  size_t vlen = 18;
  size_t extra = 2; /* space for = and NUL.  */

  buf = (char *) alloca (mlen + vlen + extra);
  memcpy (buf, macro, mlen);
  buf[mlen] = '=';
  sprintf (buf + mlen + 1, HOST_WIDE_INT_PRINT_DEC, value);

  cpp_define (parse_in, buf);
}
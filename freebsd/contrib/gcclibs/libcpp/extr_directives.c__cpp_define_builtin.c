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
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  T_DEFINE ; 
 scalar_t__ alloca (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  run_directive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 
 size_t strlen (char const*) ; 

void
_cpp_define_builtin (cpp_reader *pfile, const char *str)
{
  size_t len = strlen (str);
  char *buf = (char *) alloca (len + 1);
  memcpy (buf, str, len);
  buf[len] = '\n';
  run_directive (pfile, T_DEFINE, buf, len);
}
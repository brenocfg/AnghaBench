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
 int /*<<< orphan*/  abort () ; 
 scalar_t__ pthread_self () ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  write (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write2 (char*) ; 
 int /*<<< orphan*/  write_itoa (int,unsigned int) ; 

void
__assert_fail (const char *msg, const char *file, unsigned line, const char *func)
{
#define write2(string) write (2, (string), strlen ((string)));
  write2("mf");
#ifdef LIBMUDFLAPTH
  write2("(");
  write_itoa (2, (unsigned) pthread_self ());
  write2(")");
#endif
  write2(": assertion failure: `");
  write (2, msg, strlen (msg));
  write2("' in ");
  write (2, func, strlen (func));
  write2(" at ");
  write (2, file, strlen (file));
  write2(":");
  write_itoa (2, line);
  write2("\n");
#undef write2
  abort ();
}
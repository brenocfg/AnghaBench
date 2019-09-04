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
 int /*<<< orphan*/  fputs (char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int print_one (unsigned int namescount, const char * const * names,
                      void* data)
{
  unsigned int i;
  (void)data;
  for (i = 0; i < namescount; i++) {
    if (i > 0)
      putc(' ',stdout);
    fputs(names[i],stdout);
  }
  putc('\n',stdout);
  return 0;
}
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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ flag_dump_noaddr ; 
 scalar_t__ flag_dump_unnumbered ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 

void
dump_addr (FILE *file, const char *prefix, void *addr)
{
  if (flag_dump_noaddr || flag_dump_unnumbered)
    fprintf (file, "%s#", prefix);
  else
    fprintf (file, "%s%p", prefix, addr);
}
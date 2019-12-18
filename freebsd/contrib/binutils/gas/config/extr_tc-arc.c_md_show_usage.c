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
 int arc_mach_type ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 

void
md_show_usage (FILE *stream)
{
  fprintf (stream, "\
ARC Options:\n\
  -marc[5|6|7|8]          select processor variant (default arc%d)\n\
  -EB                     assemble code for a big endian cpu\n\
  -EL                     assemble code for a little endian cpu\n", arc_mach_type + 5);
}
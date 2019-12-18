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
 int /*<<< orphan*/  check_range () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  icheck_range () ; 
 int* isp ; 
 int /*<<< orphan*/  pc ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tos ; 
 int /*<<< orphan*/  write_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print ()
{
  if (*isp == 1)
    write_buffer (tos, stdout);
  else if (*isp == 2)
    write_buffer (tos, stderr);
  else
    fprintf (stderr, "print: illegal print destination `%ld'\n", *isp);
  isp--;
  tos--;
  icheck_range ();
  check_range ();
  pc++;
}
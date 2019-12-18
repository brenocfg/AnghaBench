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
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  xexit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_version (void)
{
  printf ("%s: version 1.0\n", program_name);
  xexit (0);
}
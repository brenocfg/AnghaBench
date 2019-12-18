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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ berkeley_format ; 
 int /*<<< orphan*/  print_berkeley_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_sysv_format (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_sizes (bfd *file)
{
  if (berkeley_format)
    print_berkeley_format (file);
  else
    print_sysv_format (file);
}
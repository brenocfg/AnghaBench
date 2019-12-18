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
struct pr_handle {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  push_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
pr_float_type (void *p, unsigned int size)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char ab[10];

  if (size == 4)
    return push_type (info, "float");
  else if (size == 8)
    return push_type (info, "double");

  sprintf (ab, "float%d", size * 8);
  return push_type (info, ab);
}
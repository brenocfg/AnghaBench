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
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ push_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
pr_int_type (void *p, unsigned int size, bfd_boolean unsignedp)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char ab[10];

  sprintf (ab, "%sint%d", unsignedp ? "u" : "", size * 8);
  return push_type (info, ab);
}
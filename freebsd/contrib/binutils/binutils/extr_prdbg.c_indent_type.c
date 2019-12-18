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
struct pr_handle {unsigned int indent; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char*) ; 

__attribute__((used)) static bfd_boolean
indent_type (struct pr_handle *info)
{
  unsigned int i;

  for (i = 0; i < info->indent; i++)
    {
      if (! append_type (info, " "))
	return FALSE;
    }

  return TRUE;
}
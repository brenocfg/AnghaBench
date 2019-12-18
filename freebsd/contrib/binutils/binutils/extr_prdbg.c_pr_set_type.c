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
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  prepend_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,char*) ; 

__attribute__((used)) static bfd_boolean
pr_set_type (void *p, bfd_boolean bitstringp)
{
  struct pr_handle *info = (struct pr_handle *) p;

  if (! substitute_type (info, ""))
    return FALSE;

  if (! prepend_type (info, "set { ")
      || ! append_type (info, " }"))
    return FALSE;

  if (bitstringp)
    {
      if (! append_type (info, "/* bitstring */"))
	return FALSE;
    }

  return TRUE;
}
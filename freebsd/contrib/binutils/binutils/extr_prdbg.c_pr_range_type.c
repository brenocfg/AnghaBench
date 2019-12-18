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
struct pr_handle {int /*<<< orphan*/ * stack; } ;
typedef  int /*<<< orphan*/  bfd_signed_vma ;
typedef  int bfd_boolean ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ append_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ prepend_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  print_vma (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,char*) ; 

__attribute__((used)) static bfd_boolean
pr_range_type (void *p, bfd_signed_vma lower, bfd_signed_vma upper)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char abl[20], abu[20];

  assert (info->stack != NULL);

  if (! substitute_type (info, ""))
    return FALSE;

  print_vma (lower, abl, FALSE, FALSE);
  print_vma (upper, abu, FALSE, FALSE);

  return (prepend_type (info, "range (")
	  && append_type (info, "):")
	  && append_type (info, abl)
	  && append_type (info, ":")
	  && append_type (info, abu));
}
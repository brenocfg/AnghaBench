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
struct ieee_range {struct ieee_range* next; int /*<<< orphan*/  low; } ;
struct ieee_handle {struct ieee_range* pending_ranges; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (struct ieee_range*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
ieee_start_range (struct ieee_handle *info, bfd_vma low)
{
  struct ieee_range *r;

  r = (struct ieee_range *) xmalloc (sizeof *r);
  memset (r, 0, sizeof *r);
  r->low = low;
  r->next = info->pending_ranges;
  info->pending_ranges = r;
  return TRUE;
}
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
typedef  int /*<<< orphan*/  tree ;
struct eh_region {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_stmt_to_eh_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_eh_region_number (struct eh_region*) ; 

__attribute__((used)) static void
record_stmt_eh_region (struct eh_region *region, tree t)
{
  if (!region)
    return;

  add_stmt_to_eh_region (t, get_eh_region_number (region));
}
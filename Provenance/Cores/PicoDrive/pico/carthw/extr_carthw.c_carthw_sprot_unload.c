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
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ sprot_item_alloc ; 
 scalar_t__ sprot_item_count ; 
 int /*<<< orphan*/ * sprot_items ; 

__attribute__((used)) static void carthw_sprot_unload(void)
{
  free(sprot_items);
  sprot_items = NULL;
  sprot_item_count = sprot_item_alloc = 0;
}
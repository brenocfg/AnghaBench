#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int mask; int addr; int /*<<< orphan*/  val; int /*<<< orphan*/  readonly; } ;

/* Variables and functions */
 int sprot_item_count ; 
 TYPE_1__* sprot_items ; 

__attribute__((used)) static u16 *carthw_sprot_get_val(u32 a, int rw_only)
{
  int i;

  for (i = 0; i < sprot_item_count; i++)
    if ((a & sprot_items[i].mask) == sprot_items[i].addr)
      if (!rw_only || !sprot_items[i].readonly)
        return &sprot_items[i].val;

  return NULL;
}
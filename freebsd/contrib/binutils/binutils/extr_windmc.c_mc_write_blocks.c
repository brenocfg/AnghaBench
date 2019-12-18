#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bin_messagetable {TYPE_1__* items; } ;
typedef  scalar_t__ rc_uint_type ;
struct TYPE_7__ {scalar_t__ vid; } ;
typedef  TYPE_2__ mc_node_lang ;
struct TYPE_8__ {scalar_t__ res_off; } ;
typedef  TYPE_3__ mc_msg_item ;
struct TYPE_6__ {int /*<<< orphan*/  highid; int /*<<< orphan*/  offset; int /*<<< orphan*/  lowid; } ;

/* Variables and functions */
 int /*<<< orphan*/  target_put_32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mc_write_blocks (struct bin_messagetable *mtbl, mc_node_lang **nl, mc_msg_item *ml, int elems)
{
  int i, idx = 0;
  rc_uint_type exid;

  if (! nl)
    return;
  i = 0;
  while (i < elems)
    {
      target_put_32 (mtbl->items[idx].lowid, nl[i]->vid);
      target_put_32 (mtbl->items[idx].highid, nl[i]->vid);
      target_put_32 (mtbl->items[idx].offset, ml[i].res_off);
      exid = nl[i++]->vid;
      while (i < elems && nl[i]->vid == exid + 1)
	{
	  target_put_32 (mtbl->items[idx].highid, nl[i]->vid);
	  exid = nl[i++]->vid;
	}
      ++idx;
    }
}
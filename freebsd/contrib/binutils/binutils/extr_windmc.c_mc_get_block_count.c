#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rc_uint_type ;
struct TYPE_3__ {scalar_t__ vid; } ;
typedef  TYPE_1__ mc_node_lang ;

/* Variables and functions */

__attribute__((used)) static int
mc_get_block_count (mc_node_lang **nl, int elems)
{
  rc_uint_type exid;
  int i, ret;

  if (! nl)
    return 0;
  i = 0;
  ret = 0;
  while (i < elems)
    {
      ret++;
      exid = nl[i++]->vid;
      while (i < elems && nl[i]->vid == exid + 1)
	exid = nl[i++]->vid;
    }
  return ret;
}
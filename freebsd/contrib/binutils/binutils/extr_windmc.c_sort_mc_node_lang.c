#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ vid; TYPE_1__* lang; } ;
typedef  TYPE_2__ mc_node_lang ;
struct TYPE_3__ {scalar_t__ nval; } ;

/* Variables and functions */

__attribute__((used)) static int
sort_mc_node_lang (const void *l, const void *r)
{
  const mc_node_lang *l1 = *((const mc_node_lang **)l);
  const mc_node_lang *r1 = *((const mc_node_lang **)r);

  if (l == r)
    return 0;
  if (l1->lang != r1->lang)
    {
      if (l1->lang->nval < r1->lang->nval)
	return -1;
      return 1;
    }
  if (l1->vid == r1->vid)
    return 0;
  if (l1->vid < r1->vid)
    return -1;
  return 1;
}
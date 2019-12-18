#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* cfm_next; } ;
typedef  TYPE_1__ cf_map_t ;

/* Variables and functions */
 TYPE_1__* head_map ; 
 scalar_t__ process_one_regular_map (TYPE_1__*) ; 

int
process_all_regular_maps(void)
{
  cf_map_t *tmp_map = head_map;

  /*
   * If the amd.conf file only has a [global] section (pretty useless
   * IMHO), there's nothing to process
   */
  if (!tmp_map)
    return 0;

  while (tmp_map) {
    if (process_one_regular_map(tmp_map) != 0)
      return 1;
    tmp_map = tmp_map->cfm_next;
  }
  return 0;
}
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
struct TYPE_4__ {struct TYPE_4__* cfm_next; int /*<<< orphan*/  cfm_dir; } ;
typedef  TYPE_1__ cf_map_t ;

/* Variables and functions */
 scalar_t__ STREQ (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* head_map ; 

cf_map_t *
find_cf_map(const char *name)
{

  cf_map_t *tmp_map = head_map;

  if (!tmp_map || !name)
    return NULL;

  while (tmp_map) {
    if (STREQ(tmp_map->cfm_dir, name)) {
      return tmp_map;
    }
    tmp_map = tmp_map->cfm_next;
  }
  return NULL;
}
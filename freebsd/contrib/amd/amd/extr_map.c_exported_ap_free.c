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
struct TYPE_4__ {size_t am_mapno; } ;
typedef  TYPE_1__ am_node ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (TYPE_1__*) ; 
 int /*<<< orphan*/ ** exported_ap ; 
 size_t first_free_map ; 
 size_t last_used_map ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
exported_ap_free(am_node *mp)
{
  /*
   * Sanity check
   */
  if (!mp)
    return;

  /*
   * Zero the slot pointer to avoid double free's
   */
  exported_ap[mp->am_mapno] = NULL;

  /*
   * Update the free and last_used indices
   */
  if (mp->am_mapno == last_used_map)
    while (last_used_map >= 0 && exported_ap[last_used_map] == 0)
      --last_used_map;

  if (first_free_map > mp->am_mapno)
    first_free_map = mp->am_mapno;

  /*
   * Free the mount node, and zero out it's internal struct data.
   */
  memset((char *) mp, 0, sizeof(am_node));
  XFREE(mp);
}
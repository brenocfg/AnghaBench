#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int am_flags; } ;
typedef  TYPE_1__ am_node ;

/* Variables and functions */
 int AMF_ROOT ; 
 TYPE_1__** exported_ap ; 
 TYPE_1__* find_ap_recursive (char*,TYPE_1__*) ; 
 int last_used_map ; 

am_node *
find_ap(char *dir)
{
  int i;

  for (i = last_used_map; i >= 0; --i) {
    am_node *mp = exported_ap[i];
    if (mp && (mp->am_flags & AMF_ROOT)) {
      mp = find_ap_recursive(dir, exported_ap[i]);
      if (mp) {
	return mp;
      }
    }
  }

  return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  am_path; } ;
typedef  TYPE_1__ am_node ;

/* Variables and functions */
 scalar_t__ STREQ (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* get_first_exported_ap (int*) ; 
 TYPE_1__* get_next_exported_ap (int*) ; 

am_node *
path_to_exported_ap(char *path)
{
  int index;
  am_node *mp;

  mp = get_first_exported_ap(&index);
  while (mp != NULL) {
    if (STREQ(mp->am_path, path))
      break;
    mp = get_next_exported_ap(&index);
  }
  return mp;
}
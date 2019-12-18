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
struct TYPE_4__ {scalar_t__ am_parent; } ;
typedef  TYPE_1__ am_node ;

/* Variables and functions */
 TYPE_1__* find_ap (char*) ; 
 scalar_t__ root_node ; 

__attribute__((used)) static am_node *
get_root_ap(char *dir)
{
  am_node *mp = find_ap(dir);

  if (mp && mp->am_parent == root_node)
    return mp;

  return 0;
}
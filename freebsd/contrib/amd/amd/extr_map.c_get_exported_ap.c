#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  am_node ;

/* Variables and functions */
 int /*<<< orphan*/ ** exported_ap ; 
 int exported_ap_size ; 

am_node *
get_exported_ap(int index)
{
  if (index < 0 || index >= exported_ap_size)
    return 0;
  return exported_ap[index];
}
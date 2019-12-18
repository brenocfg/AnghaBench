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
struct TYPE_4__ {int /*<<< orphan*/  fs_type; } ;
typedef  TYPE_1__ am_ops ;

/* Variables and functions */
 scalar_t__ STREQ (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__** vops ; 

am_ops *
ops_search(char *type)
{
  am_ops **vp;
  am_ops *rop = NULL;
  for (vp = vops; (rop = *vp); vp++)
    if (STREQ(rop->fs_type, type))
      break;
  return rop;
}
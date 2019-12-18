#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* tree_ann_t ;
typedef  enum tree_ann_type { ____Placeholder_tree_ann_type } tree_ann_type ;
struct TYPE_4__ {int type; } ;
struct TYPE_5__ {TYPE_1__ common; } ;

/* Variables and functions */

__attribute__((used)) static inline enum tree_ann_type
ann_type (tree_ann_t ann)
{
  return ann->common.type;
}
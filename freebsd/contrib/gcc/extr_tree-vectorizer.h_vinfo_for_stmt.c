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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/ * stmt_vec_info ;
typedef  TYPE_2__* stmt_ann_t ;
struct TYPE_4__ {scalar_t__ aux; } ;
struct TYPE_5__ {TYPE_1__ common; } ;

/* Variables and functions */
 TYPE_2__* stmt_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline stmt_vec_info
vinfo_for_stmt (tree stmt)
{
  stmt_ann_t ann = stmt_ann (stmt);
  return ann ? (stmt_vec_info) ann->common.aux : NULL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* stmt_ann_t ;
typedef  int /*<<< orphan*/ * bitmap ;
struct TYPE_3__ {int /*<<< orphan*/ * addresses_taken; } ;

/* Variables and functions */
 TYPE_1__* stmt_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bitmap
addresses_taken (tree stmt)
{
  stmt_ann_t ann = stmt_ann (stmt);
  return ann ? ann->addresses_taken : NULL;
}
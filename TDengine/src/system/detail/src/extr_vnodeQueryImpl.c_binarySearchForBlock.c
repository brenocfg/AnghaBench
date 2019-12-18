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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  order; } ;
struct TYPE_5__ {TYPE_1__ order; int /*<<< orphan*/  numOfBlocks; int /*<<< orphan*/  pBlock; } ;
typedef  TYPE_2__ SQuery ;

/* Variables and functions */
 int /*<<< orphan*/  binarySearchForBlockImpl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t binarySearchForBlock(SQuery *pQuery, int64_t key) {
  return binarySearchForBlockImpl(pQuery->pBlock, pQuery->numOfBlocks, key, pQuery->order.order);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lengths; } ;
struct TYPE_5__ {int /*<<< orphan*/  length_; scalar_t__ type_; scalar_t__ idx_; TYPE_2__ const* split_; } ;
typedef  TYPE_1__ BlockSplitIterator ;
typedef  TYPE_2__ BlockSplit ;

/* Variables and functions */

__attribute__((used)) static void InitBlockSplitIterator(BlockSplitIterator* self,
    const BlockSplit* split) {
  self->split_ = split;
  self->idx_ = 0;
  self->type_ = 0;
  self->length_ = split->lengths ? split->lengths[0] : 0;
}
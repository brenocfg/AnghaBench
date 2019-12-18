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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  block_split_code_; int /*<<< orphan*/  num_block_types_; int /*<<< orphan*/  num_blocks_; int /*<<< orphan*/  block_lengths_; int /*<<< orphan*/  block_types_; } ;
typedef  int /*<<< orphan*/  HuffmanTree ;
typedef  TYPE_1__ BlockEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  BuildAndStoreBlockSplitCode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void BuildAndStoreBlockSwitchEntropyCodes(BlockEncoder* self,
    HuffmanTree* tree, size_t* storage_ix, uint8_t* storage) {
  BuildAndStoreBlockSplitCode(self->block_types_, self->block_lengths_,
      self->num_blocks_, self->num_block_types_, tree, &self->block_split_code_,
      storage_ix, storage);
}
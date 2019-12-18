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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  type_histo ;
typedef  int /*<<< orphan*/  length_histo ;
struct TYPE_4__ {int /*<<< orphan*/ * length_bits; int /*<<< orphan*/ * length_depths; int /*<<< orphan*/ * type_bits; int /*<<< orphan*/ * type_depths; } ;
typedef  int /*<<< orphan*/  HuffmanTree ;
typedef  int /*<<< orphan*/  BlockTypeCodeCalculator ;
typedef  TYPE_1__ BlockSplitCode ;

/* Variables and functions */
 int BROTLI_MAX_BLOCK_TYPE_SYMBOLS ; 
 int BROTLI_NUM_BLOCK_LEN_SYMBOLS ; 
 size_t BlockLengthPrefixCode (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  BuildAndStoreHuffmanTree (int /*<<< orphan*/ *,size_t const,size_t const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitBlockTypeCodeCalculator (int /*<<< orphan*/ *) ; 
 size_t NextBlockTypeCode (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  StoreBlockSwitch (TYPE_1__*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StoreVarLenUint8 (size_t const,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static void BuildAndStoreBlockSplitCode(const uint8_t* types,
                                        const uint32_t* lengths,
                                        const size_t num_blocks,
                                        const size_t num_types,
                                        HuffmanTree* tree,
                                        BlockSplitCode* code,
                                        size_t* storage_ix,
                                        uint8_t* storage) {
  uint32_t type_histo[BROTLI_MAX_BLOCK_TYPE_SYMBOLS];
  uint32_t length_histo[BROTLI_NUM_BLOCK_LEN_SYMBOLS];
  size_t i;
  BlockTypeCodeCalculator type_code_calculator;
  memset(type_histo, 0, (num_types + 2) * sizeof(type_histo[0]));
  memset(length_histo, 0, sizeof(length_histo));
  InitBlockTypeCodeCalculator(&type_code_calculator);
  for (i = 0; i < num_blocks; ++i) {
    size_t type_code = NextBlockTypeCode(&type_code_calculator, types[i]);
    if (i != 0) ++type_histo[type_code];
    ++length_histo[BlockLengthPrefixCode(lengths[i])];
  }
  StoreVarLenUint8(num_types - 1, storage_ix, storage);
  if (num_types > 1) {  /* TODO: else? could StoreBlockSwitch occur? */
    BuildAndStoreHuffmanTree(&type_histo[0], num_types + 2, num_types + 2, tree,
                             &code->type_depths[0], &code->type_bits[0],
                             storage_ix, storage);
    BuildAndStoreHuffmanTree(&length_histo[0], BROTLI_NUM_BLOCK_LEN_SYMBOLS,
                             BROTLI_NUM_BLOCK_LEN_SYMBOLS,
                             tree, &code->length_depths[0],
                             &code->length_bits[0], storage_ix, storage);
    StoreBlockSwitch(code, lengths[0], types[0], 1, storage_ix, storage);
  }
}
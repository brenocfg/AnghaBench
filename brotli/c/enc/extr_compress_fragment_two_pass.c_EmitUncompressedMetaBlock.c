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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliStoreMetaBlockHeader (size_t,int,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,size_t) ; 

__attribute__((used)) static void EmitUncompressedMetaBlock(const uint8_t* input, size_t input_size,
                                      size_t* storage_ix, uint8_t* storage) {
  BrotliStoreMetaBlockHeader(input_size, 1, storage_ix, storage);
  *storage_ix = (*storage_ix + 7u) & ~7u;
  memcpy(&storage[*storage_ix >> 3], input, input_size);
  *storage_ix += input_size << 3;
  storage[*storage_ix >> 3] = 0;
}
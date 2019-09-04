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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliEncodeMlen (size_t,int*,size_t*,int*) ; 
 int /*<<< orphan*/  BrotliWriteBits (int,int,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void BrotliStoreUncompressedMetaBlockHeader(size_t length,
                                                   size_t* storage_ix,
                                                   uint8_t* storage) {
  uint64_t lenbits;
  size_t nlenbits;
  uint64_t nibblesbits;

  /* Write ISLAST bit.
     Uncompressed block cannot be the last one, so set to 0. */
  BrotliWriteBits(1, 0, storage_ix, storage);
  BrotliEncodeMlen(length, &lenbits, &nlenbits, &nibblesbits);
  BrotliWriteBits(2, nibblesbits, storage_ix, storage);
  BrotliWriteBits(nlenbits, lenbits, storage_ix, storage);
  /* Write ISUNCOMPRESSED bit. */
  BrotliWriteBits(1, 1, storage_ix, storage);
}
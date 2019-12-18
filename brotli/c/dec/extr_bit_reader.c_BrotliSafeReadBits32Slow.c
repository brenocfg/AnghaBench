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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  BrotliBitReaderState ;
typedef  int /*<<< orphan*/  BrotliBitReader ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_DCHECK (int) ; 
 int /*<<< orphan*/  BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 int /*<<< orphan*/  BrotliBitReaderRestoreState (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BrotliBitReaderSaveState (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BrotliSafeReadBits (int /*<<< orphan*/ * const,int,int*) ; 

BROTLI_BOOL BrotliSafeReadBits32Slow(BrotliBitReader* const br,
    uint32_t n_bits, uint32_t* val) {
  uint32_t low_val;
  uint32_t high_val;
  BrotliBitReaderState memento;
  BROTLI_DCHECK(n_bits <= 32);
  BROTLI_DCHECK(n_bits > 24);
  BrotliBitReaderSaveState(br, &memento);
  if (!BrotliSafeReadBits(br, 16, &low_val) ||
      !BrotliSafeReadBits(br, n_bits - 16, &high_val)) {
    BrotliBitReaderRestoreState(br, &memento);
    return BROTLI_FALSE;
  }
  *val = low_val | (high_val << 16);
  return BROTLI_TRUE;
}
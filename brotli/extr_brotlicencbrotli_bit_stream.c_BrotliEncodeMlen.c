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
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_DCHECK (int) ; 
 int Log2FloorNonZero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void BrotliEncodeMlen(size_t length, uint64_t* bits,
                             size_t* numbits, uint64_t* nibblesbits) {
  size_t lg = (length == 1) ? 1 : Log2FloorNonZero((uint32_t)(length - 1)) + 1;
  size_t mnibbles = (lg < 16 ? 16 : (lg + 3)) / 4;
  BROTLI_DCHECK(length > 0);
  BROTLI_DCHECK(length <= (1 << 24));
  BROTLI_DCHECK(lg <= 24);
  *nibblesbits = mnibbles - 4;
  *numbits = mnibbles * 4;
  *bits = length - 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/ * wkdecompscratch; int /*<<< orphan*/ * lz4decodestate; } ;
typedef  TYPE_1__ compressor_decode_scratch_t ;
struct TYPE_4__ {int lz4_decompressions; int lz4_decompressed_bytes; int wk_decompressions; int wk_decompressed_bytes; } ;

/* Variables and functions */
 scalar_t__ CCLZ4 ; 
 scalar_t__ CCWK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_DECOMPRESSOR_STAT (int) ; 
 int /*<<< orphan*/  WKdmD (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertf (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ compressor_stats ; 
 int /*<<< orphan*/ * d32 ; 
 scalar_t__ lz4raw_decode_buffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 

void metadecompressor(const uint8_t *source, uint8_t *dest, uint32_t csize, uint16_t ccodec, void *compressor_dscratchin) {
	int dolz4 = (ccodec == CCLZ4);
	int rval;
	compressor_decode_scratch_t *compressor_dscratch = compressor_dscratchin;
	
	if (dolz4) {
		rval = (int)lz4raw_decode_buffer(dest, PAGE_SIZE, source, csize, &compressor_dscratch->lz4decodestate[0]);
		VM_DECOMPRESSOR_STAT(compressor_stats.lz4_decompressions+=1);
		VM_DECOMPRESSOR_STAT(compressor_stats.lz4_decompressed_bytes+=csize);
#if DEVELOPMENT || DEBUG
		uint32_t *d32 = dest;
#endif
		assertf(rval == PAGE_SIZE, "LZ4 decode: size != pgsize %d, header: 0x%x, 0x%x, 0x%x",
		    rval, *d32, *(d32+1), *(d32+2));
	} else {
		assert(ccodec == CCWK);

		WKdmD(source, dest, &compressor_dscratch->wkdecompscratch[0], csize);

		VM_DECOMPRESSOR_STAT(compressor_stats.wk_decompressions+=1);
		VM_DECOMPRESSOR_STAT(compressor_stats.wk_decompressed_bytes+=csize);
	}
}
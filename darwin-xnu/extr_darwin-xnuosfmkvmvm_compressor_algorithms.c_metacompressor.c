#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum compressor_preselect_t { ____Placeholder_compressor_preselect_t } compressor_preselect_t ;
struct TYPE_4__ {int /*<<< orphan*/ * lz4state; int /*<<< orphan*/ * wkscratch; } ;
typedef  TYPE_1__ compressor_encode_scratch_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int wk_compressed_bytes_total; int /*<<< orphan*/  wk_compressed_bytes_exclusive; int /*<<< orphan*/  wk_compressions_exclusive; int /*<<< orphan*/  wk_sv_compressions; int /*<<< orphan*/  wk_compression_failures; int /*<<< orphan*/  wk_compressions; } ;
struct TYPE_5__ {int lz4_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCLZ4 ; 
 int /*<<< orphan*/  CCWK ; 
 scalar_t__ CMODE_HYB ; 
 scalar_t__ CMODE_LZ4 ; 
 scalar_t__ CMODE_WK ; 
 int CPRESELLZ4 ; 
 int CPRESELWK ; 
 int CSKIPLZ4 ; 
 int FALSE ; 
 int PAGE_SIZE ; 
 int TRUE ; 
 int /*<<< orphan*/  VM_COMPRESSOR_STAT (int) ; 
 int WKdmC (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int compressor_preselect () ; 
 int /*<<< orphan*/  compressor_selector_update (int,int,int) ; 
 TYPE_3__ compressor_stats ; 
 scalar_t__ lz4raw_encode_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ vm_compressor_current_codec ; 
 TYPE_2__ vmctune ; 
 int wkc ; 

int metacompressor(const uint8_t *in, uint8_t *cdst, int32_t outbufsz, uint16_t *codec, void *cscratchin, boolean_t *incomp_copy) {
	int sz = -1;
	int dowk = FALSE, dolz4 = FALSE, skiplz4 = FALSE;
	int insize = PAGE_SIZE;
	compressor_encode_scratch_t *cscratch = cscratchin;

	if (vm_compressor_current_codec == CMODE_WK) {
		dowk = TRUE;
	} else if (vm_compressor_current_codec == CMODE_LZ4) {
		dolz4 = TRUE;
	} else if (vm_compressor_current_codec == CMODE_HYB) {
		enum compressor_preselect_t presel = compressor_preselect();
		if (presel == CPRESELLZ4) {
			dolz4 = TRUE;
			goto lz4compress;
		} else if (presel == CSKIPLZ4) {
			dowk = TRUE;
			skiplz4 = TRUE;
		} else {
			assert(presel == CPRESELWK);
			dowk = TRUE;
		}
	}

	if (dowk) {
		*codec = CCWK;
		VM_COMPRESSOR_STAT(compressor_stats.wk_compressions++);
		sz = WKdmC(in, cdst, &cscratch->wkscratch[0], incomp_copy, outbufsz);

		if (sz == -1) {
			VM_COMPRESSOR_STAT(compressor_stats.wk_compressed_bytes_total+=PAGE_SIZE);
			VM_COMPRESSOR_STAT(compressor_stats.wk_compression_failures++);

			if (vm_compressor_current_codec == CMODE_HYB) {
				goto lz4eval;
			}
			goto cexit;
		} else if (sz == 0) {
			VM_COMPRESSOR_STAT(compressor_stats.wk_sv_compressions++);
			VM_COMPRESSOR_STAT(compressor_stats.wk_compressed_bytes_total+=4);
		} else {
			VM_COMPRESSOR_STAT(compressor_stats.wk_compressed_bytes_total+=sz);
		}
	}
lz4eval:
	if (vm_compressor_current_codec == CMODE_HYB) {
		if (((sz == -1) || (sz >= vmctune.lz4_threshold)) && (skiplz4 == FALSE)) {
			dolz4 = TRUE;
		} else {
#if DEVELOPMENT || DEBUG
			int wkc = (sz == -1) ? PAGE_SIZE : sz;
#endif
			VM_COMPRESSOR_STAT(compressor_stats.wk_compressions_exclusive++);
			VM_COMPRESSOR_STAT(compressor_stats.wk_compressed_bytes_exclusive+=wkc);
			goto cexit;
		}
	}

lz4compress:

	if (dolz4) {
		if (sz == -1) {
			sz = PAGE_SIZE;
		}
		int wksz = sz;
		*codec = CCLZ4;

		sz = (int) lz4raw_encode_buffer(cdst, outbufsz, in, insize, &cscratch->lz4state[0]);

		compressor_selector_update(sz, dowk, wksz);
		if (sz == 0) {
			sz = -1;
			goto cexit;
		}
	}
cexit:
	return sz;
}
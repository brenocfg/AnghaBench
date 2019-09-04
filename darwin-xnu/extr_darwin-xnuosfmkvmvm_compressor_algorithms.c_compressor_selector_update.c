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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int lz4_compressed_bytes; int lz4_wk_compression_negative_delta; int /*<<< orphan*/  lz4_wk_compression_delta; int /*<<< orphan*/  lz4_compression_failures; int /*<<< orphan*/  lz4_compressions; } ;
struct TYPE_5__ {scalar_t__ lz4_run_length; int /*<<< orphan*/  lz4_total_negatives; scalar_t__ lz4_failure_run_length; int /*<<< orphan*/  lz4_total_unprofitables; int /*<<< orphan*/  lz4_total_failures; } ;
struct TYPE_4__ {int wkdm_reeval_threshold; scalar_t__ lz4_run_continue_bytes; scalar_t__ lz4_profitable_bytes; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_COMPRESSOR_STAT (int) ; 
 scalar_t__ __probable (int) ; 
 TYPE_3__ compressor_stats ; 
 TYPE_2__ vmcstate ; 
 TYPE_1__ vmctune ; 

__attribute__((used)) static inline void compressor_selector_update(int lz4sz, int didwk, int wksz) {
	VM_COMPRESSOR_STAT(compressor_stats.lz4_compressions++);

	if (lz4sz == 0) {
		VM_COMPRESSOR_STAT(compressor_stats.lz4_compressed_bytes+=PAGE_SIZE);
		VM_COMPRESSOR_STAT(compressor_stats.lz4_compression_failures++);
		vmcstate.lz4_failure_run_length++;
		VM_COMPRESSOR_STAT(vmcstate.lz4_total_failures++);
		vmcstate.lz4_run_length = 0;
	} else {
		vmcstate.lz4_failure_run_length = 0;

		VM_COMPRESSOR_STAT(compressor_stats.lz4_compressed_bytes+=lz4sz);

		if (lz4sz <= vmctune.wkdm_reeval_threshold) {
			vmcstate.lz4_run_length = 0;
		} else {
			if (!didwk) {
				vmcstate.lz4_run_length++;
			}
		}

		if (didwk) {
			if (__probable(wksz > lz4sz)) {
				uint32_t lz4delta = wksz - lz4sz;
				VM_COMPRESSOR_STAT(compressor_stats.lz4_wk_compression_delta+=lz4delta);
				if (lz4delta >= vmctune.lz4_run_continue_bytes) {
					vmcstate.lz4_run_length++;
				} else if (lz4delta <= vmctune.lz4_profitable_bytes) {
					vmcstate.lz4_failure_run_length++;
					VM_COMPRESSOR_STAT(vmcstate.lz4_total_unprofitables++);
					vmcstate.lz4_run_length = 0;
				} else {
					vmcstate.lz4_run_length = 0;
				}
			} else {
				VM_COMPRESSOR_STAT(compressor_stats.lz4_wk_compression_negative_delta+=(lz4sz-wksz));
				vmcstate.lz4_failure_run_length++;
				VM_COMPRESSOR_STAT(vmcstate.lz4_total_negatives++);
				vmcstate.lz4_run_length = 0;
			}
		}
	}
}
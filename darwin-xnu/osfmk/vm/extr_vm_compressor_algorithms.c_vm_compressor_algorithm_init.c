#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_compressor_mode_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  tmpc ;
typedef  int /*<<< orphan*/  new_codec ;
struct TYPE_2__ {int lz4_threshold; } ;

/* Variables and functions */
 scalar_t__ CMODE_HYB ; 
 scalar_t__ CMODE_LZ4 ; 
 scalar_t__ CMODE_WK ; 
 int PAGE_SIZE ; 
 scalar_t__ PE_parse_boot_argn (char*,scalar_t__*,int) ; 
 scalar_t__ VM_COMPRESSOR_DEFAULT_CODEC ; 
 int /*<<< orphan*/  assertf (int,char*,scalar_t__) ; 
 scalar_t__ vm_compressor_current_codec ; 
 TYPE_1__ vmctune ; 

void vm_compressor_algorithm_init(void) {
	vm_compressor_mode_t new_codec = VM_COMPRESSOR_DEFAULT_CODEC;

#if defined(__arm64__)
	new_codec = CMODE_HYB;

	if (PAGE_SIZE == 16384) {
		vmctune.lz4_threshold = 12288;
	}
#endif

	PE_parse_boot_argn("vm_compressor_codec", &new_codec, sizeof(new_codec));
	assertf(((new_codec == VM_COMPRESSOR_DEFAULT_CODEC) || (new_codec == CMODE_WK) ||
		(new_codec == CMODE_LZ4) || (new_codec == CMODE_HYB)),
	    "Invalid VM compression codec: %u", new_codec);

#if defined(__arm__)||defined(__arm64__)
	uint32_t tmpc;
	if (PE_parse_boot_argn("-vm_compressor_wk", &tmpc, sizeof(tmpc))) {
		new_codec = VM_COMPRESSOR_DEFAULT_CODEC;
	} else if (PE_parse_boot_argn("-vm_compressor_hybrid", &tmpc, sizeof(tmpc))) {
		new_codec = CMODE_HYB;
	}

	vm_compressor_current_codec = new_codec;
#endif /* arm/arm64 */
}
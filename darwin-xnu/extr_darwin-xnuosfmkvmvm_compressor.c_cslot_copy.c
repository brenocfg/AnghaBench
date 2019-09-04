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
typedef  TYPE_1__* c_slot_t ;
struct TYPE_4__ {int /*<<< orphan*/  c_packed_ptr; int /*<<< orphan*/  c_size; } ;

/* Variables and functions */

__attribute__((used)) static inline void cslot_copy(c_slot_t cdst, c_slot_t csrc) {
#if CHECKSUM_THE_DATA
		cdst->c_hash_data = csrc->c_hash_data;
#endif
#if CHECKSUM_THE_COMPRESSED_DATA
		cdst->c_hash_compressed_data = csrc->c_hash_compressed_data;
#endif
#if POPCOUNT_THE_COMPRESSED_DATA
		cdst->c_pop_cdata = csrc->c_pop_cdata;
#endif
		cdst->c_size = csrc->c_size;
		cdst->c_packed_ptr = csrc->c_packed_ptr;
#if defined(__arm__) || defined(__arm64__)
		cdst->c_codec = csrc->c_codec;
#endif
}
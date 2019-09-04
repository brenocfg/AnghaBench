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
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  WK_word ;

/* Variables and functions */
 int WKdm_compress_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline int WKdmC(WK_word* src_buf, WK_word* dest_buf, WK_word* scratch, boolean_t *incomp_copy, unsigned int limit) {
	(void)incomp_copy;
	int wkcval;
#if defined(__arm64__)
	if (PAGE_SIZE == 4096) {
		wkcval = WKdm_compress_4k(src_buf, dest_buf, scratch, limit);
	} else {
		__unused uint64_t wcswstart;

		VM_COMPRESSOR_STAT_DBG(wcswstart = mach_absolute_time());

		int wkswsz = WKdm_compress_16k(src_buf, dest_buf, scratch, limit);

		VM_COMPRESSOR_STAT_DBG(compressor_stats.wks_cabstime += mach_absolute_time() - wcswstart);
		VM_COMPRESSOR_STAT(compressor_stats.wks_compressions++);
		wkcval = wkswsz;
	}
#else
	wkcval = WKdm_compress_new(src_buf, dest_buf, scratch, limit);
#endif
	return wkcval;
}
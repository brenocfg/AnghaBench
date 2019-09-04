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
typedef  int /*<<< orphan*/  WK_word ;

/* Variables and functions */
 int /*<<< orphan*/  WKdm_decompress_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  WKdm_hv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void WKdmD(WK_word* src_buf, WK_word* dest_buf, WK_word* scratch, unsigned int bytes) {
#if defined(__arm64__)
#endif
	WKdm_hv(src_buf);
#if defined(__arm64__)
	if (PAGE_SIZE == 4096) {
		WKdm_decompress_4k(src_buf, dest_buf, scratch, bytes);
	} else {
		__unused uint64_t wdsstart;

		VM_COMPRESSOR_STAT_DBG(wdsstart = mach_absolute_time());
		WKdm_decompress_16k(src_buf, dest_buf, scratch, bytes);

		VM_COMPRESSOR_STAT_DBG(compressor_stats.wks_dabstime += mach_absolute_time() - wdsstart);
		VM_COMPRESSOR_STAT(compressor_stats.wks_decompressions++);
	}
#else /* !defined arm64 */
	WKdm_decompress_new(src_buf, dest_buf, scratch, bytes);
#endif
}
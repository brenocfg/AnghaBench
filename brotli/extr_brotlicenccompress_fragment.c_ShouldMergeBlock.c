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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 size_t const FastLog2 (size_t const) ; 
 int /*<<< orphan*/  TO_BROTLI_BOOL (int) ; 

__attribute__((used)) static BROTLI_BOOL ShouldMergeBlock(
    const uint8_t* data, size_t len, const uint8_t* depths) {
  size_t histo[256] = { 0 };
  static const size_t kSampleRate = 43;
  size_t i;
  for (i = 0; i < len; i += kSampleRate) {
    ++histo[data[i]];
  }
  {
    const size_t total = (len + kSampleRate - 1) / kSampleRate;
    double r = (FastLog2(total) + 0.5) * (double)total + 200;
    for (i = 0; i < 256; ++i) {
      r -= (double)histo[i] * (depths[i] + FastLog2(histo[i]));
    }
    return TO_BROTLI_BOOL(r >= 0.0);
  }
}
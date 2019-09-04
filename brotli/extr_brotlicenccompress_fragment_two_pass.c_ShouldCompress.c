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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_TRUE ; 
 double const BitsEntropy (int /*<<< orphan*/ *,int) ; 
 double MIN_RATIO ; 
 double SAMPLE_RATE ; 
 int /*<<< orphan*/  TO_BROTLI_BOOL (int) ; 

__attribute__((used)) static BROTLI_BOOL ShouldCompress(
    const uint8_t* input, size_t input_size, size_t num_literals) {
  double corpus_size = (double)input_size;
  if (num_literals < MIN_RATIO * corpus_size) {
    return BROTLI_TRUE;
  } else {
    uint32_t literal_histo[256] = { 0 };
    const double max_total_bit_cost = corpus_size * 8 * MIN_RATIO / SAMPLE_RATE;
    size_t i;
    for (i = 0; i < input_size; i += SAMPLE_RATE) {
      ++literal_histo[input[i]];
    }
    return TO_BROTLI_BOOL(BitsEntropy(literal_histo, 256) < max_total_bit_cost);
  }
}
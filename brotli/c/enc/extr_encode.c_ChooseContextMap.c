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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_DCHECK (int) ; 
 int MIN_QUALITY_FOR_HQ_CONTEXT_MODELING ; 
 double ShannonEntropy (int*,int,size_t*) ; 

__attribute__((used)) static void ChooseContextMap(int quality,
                             uint32_t* bigram_histo,
                             size_t* num_literal_contexts,
                             const uint32_t** literal_context_map) {
  static const uint32_t kStaticContextMapContinuation[64] = {
    1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  };
  static const uint32_t kStaticContextMapSimpleUTF8[64] = {
    0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  };

  uint32_t monogram_histo[3] = { 0 };
  uint32_t two_prefix_histo[6] = { 0 };
  size_t total;
  size_t i;
  size_t dummy;
  double entropy[4];
  for (i = 0; i < 9; ++i) {
    monogram_histo[i % 3] += bigram_histo[i];
    two_prefix_histo[i % 6] += bigram_histo[i];
  }
  entropy[1] = ShannonEntropy(monogram_histo, 3, &dummy);
  entropy[2] = (ShannonEntropy(two_prefix_histo, 3, &dummy) +
                ShannonEntropy(two_prefix_histo + 3, 3, &dummy));
  entropy[3] = 0;
  for (i = 0; i < 3; ++i) {
    entropy[3] += ShannonEntropy(bigram_histo + 3 * i, 3, &dummy);
  }

  total = monogram_histo[0] + monogram_histo[1] + monogram_histo[2];
  BROTLI_DCHECK(total != 0);
  entropy[0] = 1.0 / (double)total;
  entropy[1] *= entropy[0];
  entropy[2] *= entropy[0];
  entropy[3] *= entropy[0];

  if (quality < MIN_QUALITY_FOR_HQ_CONTEXT_MODELING) {
    /* 3 context models is a bit slower, don't use it at lower qualities. */
    entropy[3] = entropy[1] * 10;
  }
  /* If expected savings by symbol are less than 0.2 bits, skip the
     context modeling -- in exchange for faster decoding speed. */
  if (entropy[1] - entropy[2] < 0.2 &&
      entropy[1] - entropy[3] < 0.2) {
    *num_literal_contexts = 1;
  } else if (entropy[2] - entropy[3] < 0.02) {
    *num_literal_contexts = 2;
    *literal_context_map = kStaticContextMapSimpleUTF8;
  } else {
    *num_literal_contexts = 3;
    *literal_context_map = kStaticContextMapContinuation;
  }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {size_t literal_histograms_size; size_t command_histograms_size; size_t distance_histograms_size; TYPE_2__* distance_histograms; TYPE_1__* command_histograms; TYPE_3__* literal_histograms; } ;
struct TYPE_8__ {int /*<<< orphan*/  data_; } ;
struct TYPE_7__ {int /*<<< orphan*/  data_; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_; } ;
typedef  TYPE_4__ MetaBlockSplit ;

/* Variables and functions */
 int BROTLI_NUM_COMMAND_SYMBOLS ; 
 int /*<<< orphan*/  BrotliOptimizeHuffmanCountsForRle (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void BrotliOptimizeHistograms(uint32_t num_distance_codes,
                              MetaBlockSplit* mb) {
  uint8_t good_for_rle[BROTLI_NUM_COMMAND_SYMBOLS];
  size_t i;
  for (i = 0; i < mb->literal_histograms_size; ++i) {
    BrotliOptimizeHuffmanCountsForRle(256, mb->literal_histograms[i].data_,
                                      good_for_rle);
  }
  for (i = 0; i < mb->command_histograms_size; ++i) {
    BrotliOptimizeHuffmanCountsForRle(BROTLI_NUM_COMMAND_SYMBOLS,
                                      mb->command_histograms[i].data_,
                                      good_for_rle);
  }
  for (i = 0; i < mb->distance_histograms_size; ++i) {
    BrotliOptimizeHuffmanCountsForRle(num_distance_codes,
                                      mb->distance_histograms[i].data_,
                                      good_for_rle);
  }
}
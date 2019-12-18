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
typedef  int WK_word ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINT_2 (char*,int) ; 
 int TWO_BITS_PACKING_MASK ; 

__attribute__((used)) static WK_word*
WK_unpack_2bits(WK_word *input_buf,
                WK_word *input_end,
                WK_word *output_buf) {

  WK_word *input_next = input_buf;
  WK_word *output_next = output_buf;
  WK_word packing_mask = TWO_BITS_PACKING_MASK;

  /* loop to repeatedly grab one input word and unpack it into
   * 4 output words.  This loop could be unrolled a little---it's
   * designed to be easy to do that.
   */   
  while (input_next < input_end) {
    WK_word temp = input_next[0];
    DEBUG_PRINT_2("Unpacked tags word: %.8x\n", temp);
    output_next[0] = temp & packing_mask;
    output_next[1] = (temp >> 2) & packing_mask;
    output_next[2] = (temp >> 4) & packing_mask;
    output_next[3] = (temp >> 6) & packing_mask;
    
    output_next += 4;
    input_next++;
  }

  return output_next;

}
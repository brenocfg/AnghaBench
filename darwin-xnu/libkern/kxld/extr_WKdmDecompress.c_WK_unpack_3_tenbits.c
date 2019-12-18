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
 int LOW_BITS_MASK ; 

__attribute__((used)) static WK_word*
WK_unpack_3_tenbits(WK_word *input_buf,
                    WK_word *input_end,
                    WK_word *output_buf) {

  WK_word *input_next = input_buf;
  WK_word *output_next = output_buf;
  WK_word packing_mask = LOW_BITS_MASK;
  
  /* loop to fetch words of input, splitting each into three
   * words of output with 10 meaningful low bits.  This loop
   * probably ought to be unrolled and maybe coiled
   */
  while (input_next < input_end) {
    WK_word temp = input_next[0];
    
    output_next[0] = temp & packing_mask;
    output_next[1] = (temp >> 10) & packing_mask;
    output_next[2] = temp >> 20;
    
    input_next++;
    output_next += 3;
  }
  
  return output_next;

}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
struct TYPE_3__ {int plainchar; int step; } ;
typedef  TYPE_1__ base64_decodestate ;

/* Variables and functions */
 int /*<<< orphan*/  base64_decode_value_signed (int /*<<< orphan*/ ) ; 
#define  step_a 131 
#define  step_b 130 
#define  step_c 129 
#define  step_d 128 

__attribute__((used)) static int base64_decode_block_signed(const int8_t* code_in, const int length_in, int8_t* plaintext_out, base64_decodestate* state_in){
  const int8_t* codechar = code_in;
  int8_t* plainchar = plaintext_out;
  int8_t fragment;
  
  *plainchar = state_in->plainchar;
  
  switch (state_in->step){
    while (1){
      case step_a:
        do {
          if (codechar == code_in+length_in){
            state_in->step = step_a;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }
          fragment = (int8_t)base64_decode_value_signed(*codechar++);
        } while (fragment < 0);
        *plainchar    = (fragment & 0x03f) << 2;
      case step_b:
        do {
          if (codechar == code_in+length_in){
            state_in->step = step_b;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }
          fragment = (int8_t)base64_decode_value_signed(*codechar++);
        } while (fragment < 0);
        *plainchar++ |= (fragment & 0x030) >> 4;
        *plainchar    = (fragment & 0x00f) << 4;
      case step_c:
        do {
          if (codechar == code_in+length_in){
            state_in->step = step_c;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }
          fragment = (int8_t)base64_decode_value_signed(*codechar++);
        } while (fragment < 0);
        *plainchar++ |= (fragment & 0x03c) >> 2;
        *plainchar    = (fragment & 0x003) << 6;
      case step_d:
        do {
          if (codechar == code_in+length_in){
            state_in->step = step_d;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }
          fragment = (int8_t)base64_decode_value_signed(*codechar++);
        } while (fragment < 0);
        *plainchar++   |= (fragment & 0x03f);
    }
  }
  /* control should not reach here */
  return plainchar - plaintext_out;
}
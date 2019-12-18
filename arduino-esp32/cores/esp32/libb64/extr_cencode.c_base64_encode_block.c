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
struct TYPE_3__ {char result; int step; } ;
typedef  TYPE_1__ base64_encodestate ;

/* Variables and functions */
 void* base64_encode_value (char) ; 
#define  step_A 130 
#define  step_B 129 
#define  step_C 128 

int base64_encode_block(const char* plaintext_in, int length_in, char* code_out, base64_encodestate* state_in)
{
    const char* plainchar = plaintext_in;
    const char* const plaintextend = plaintext_in + length_in;
    char* codechar = code_out;
    char result;
    char fragment;

    result = state_in->result;

    switch (state_in->step) {
        while (1) {
        case step_A:
            if (plainchar == plaintextend) {
                state_in->result = result;
                state_in->step = step_A;
                return codechar - code_out;
            }
            fragment = *plainchar++;
            result = (fragment & 0x0fc) >> 2;
            *codechar++ = base64_encode_value(result);
            result = (fragment & 0x003) << 4;
        case step_B:
            if (plainchar == plaintextend) {
                state_in->result = result;
                state_in->step = step_B;
                return codechar - code_out;
            }
            fragment = *plainchar++;
            result |= (fragment & 0x0f0) >> 4;
            *codechar++ = base64_encode_value(result);
            result = (fragment & 0x00f) << 2;
        case step_C:
            if (plainchar == plaintextend) {
                state_in->result = result;
                state_in->step = step_C;
                return codechar - code_out;
            }
            fragment = *plainchar++;
            result |= (fragment & 0x0c0) >> 6;
            *codechar++ = base64_encode_value(result);
            result  = (fragment & 0x03f) >> 0;
            *codechar++ = base64_encode_value(result);
        }
    }
    /* control should not reach here */
    return codechar - code_out;
}
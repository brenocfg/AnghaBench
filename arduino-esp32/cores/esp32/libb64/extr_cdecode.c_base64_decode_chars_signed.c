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
typedef  scalar_t__ int8_t ;
typedef  int /*<<< orphan*/  base64_decodestate ;

/* Variables and functions */
 int base64_decode_block_signed (scalar_t__ const*,int const,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base64_init_decodestate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int base64_decode_chars_signed(const int8_t* code_in, const int length_in, int8_t* plaintext_out){
  base64_decodestate _state;
  base64_init_decodestate(&_state);
  int len = base64_decode_block_signed(code_in, length_in, plaintext_out, &_state);
  if(len > 0) plaintext_out[len] = 0;
  return len;
}
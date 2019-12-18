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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  base64_decodestate ;

/* Variables and functions */
 int base64_decode_block_signed (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int base64_decode_block(const char* code_in, const int length_in, char* plaintext_out, base64_decodestate* state_in){
  return base64_decode_block_signed((int8_t *) code_in, length_in, (int8_t *) plaintext_out, state_in);
}
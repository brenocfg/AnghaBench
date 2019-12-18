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
typedef  int /*<<< orphan*/  base64_encodestate ;

/* Variables and functions */
 int base64_encode_block (char const*,int,char*,int /*<<< orphan*/ *) ; 
 int base64_encode_blockend (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base64_init_encodestate (int /*<<< orphan*/ *) ; 

int base64_encode_chars(const char* plaintext_in, int length_in, char* code_out)
{
    base64_encodestate _state;
    base64_init_encodestate(&_state);
    int len = base64_encode_block(plaintext_in, length_in, code_out, &_state);
    return len + base64_encode_blockend((code_out + len), &_state);
}
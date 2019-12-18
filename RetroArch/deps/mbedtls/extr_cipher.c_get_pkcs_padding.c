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

/* Variables and functions */
 int MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_CIPHER_INVALID_PADDING ; 

__attribute__((used)) static int get_pkcs_padding( unsigned char *input, size_t input_len,
        size_t *data_len )
{
    size_t i, pad_idx;
    unsigned char padding_len, bad = 0;

    if( NULL == input || NULL == data_len )
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );

    padding_len = input[input_len - 1];
    *data_len = input_len - padding_len;

    /* Avoid logical || since it results in a branch */
    bad |= padding_len > input_len;
    bad |= padding_len == 0;

    /* The number of bytes checked must be independent of padding_len,
     * so pick input_len, which is usually 8 or 16 (one block) */
    pad_idx = input_len - padding_len;
    for( i = 0; i < input_len; i++ )
        bad |= ( input[i] ^ padding_len ) * ( i >= pad_idx );

    return( MBEDTLS_ERR_CIPHER_INVALID_PADDING * ( bad != 0 ) );
}
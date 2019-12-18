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
typedef  int /*<<< orphan*/  esp_aes_context ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_AES_ENCRYPT ; 
 int MBEDTLS_ERR_AES_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_AES_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  esp_aes_acquire_hardware () ; 
 int /*<<< orphan*/  esp_aes_block (int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  esp_aes_release_hardware () ; 
 int /*<<< orphan*/  esp_aes_setkey_hardware (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_key_length (int /*<<< orphan*/ *) ; 

int esp_aes_crypt_ofb( esp_aes_context *ctx,
                           size_t length,
                           size_t *iv_off,
                           unsigned char iv[16],
                           const unsigned char *input,
                           unsigned char *output )
{
    int ret = 0;
    size_t n;

    if ( ctx == NULL || iv_off == NULL || iv == NULL ||
        input == NULL || output == NULL ) {
            return MBEDTLS_ERR_AES_BAD_INPUT_DATA;
    }

    n = *iv_off;

    if( n > 15 ) {
        return( MBEDTLS_ERR_AES_BAD_INPUT_DATA );
    }

    if (!valid_key_length(ctx)) {
        return MBEDTLS_ERR_AES_INVALID_KEY_LENGTH;
    }

    esp_aes_acquire_hardware();

    esp_aes_setkey_hardware(ctx, ESP_AES_ENCRYPT);

    while( length-- ) {
        if( n == 0 ) {
            esp_aes_block(ctx, iv, iv);
        }
        *output++ =  *input++ ^ iv[n];

        n = ( n + 1 ) & 0x0F;
    }

    *iv_off = n;

    esp_aes_release_hardware();

    return( ret );
}
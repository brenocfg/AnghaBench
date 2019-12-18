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
 int /*<<< orphan*/  esp_aes_acquire_hardware () ; 
 int /*<<< orphan*/  esp_aes_block (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  esp_aes_release_hardware () ; 
 int /*<<< orphan*/  esp_aes_setkey_hardware (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int esp_aes_crypt_ctr( esp_aes_context *ctx,
                       size_t length,
                       size_t *nc_off,
                       unsigned char nonce_counter[16],
                       unsigned char stream_block[16],
                       const unsigned char *input,
                       unsigned char *output )
{
    int c, i;
    size_t n = *nc_off;

    esp_aes_acquire_hardware();

    esp_aes_setkey_hardware(ctx, ESP_AES_ENCRYPT);

    while ( length-- ) {
        if ( n == 0 ) {
            esp_aes_block(nonce_counter, stream_block);

            for ( i = 16; i > 0; i-- )
                if ( ++nonce_counter[i - 1] != 0 ) {
                    break;
                }
        }
        c = *input++;
        *output++ = (unsigned char)( c ^ stream_block[n] );

        n = ( n + 1 ) & 0x0F;
    }

    *nc_off = n;

    esp_aes_release_hardware();

    return 0;
}
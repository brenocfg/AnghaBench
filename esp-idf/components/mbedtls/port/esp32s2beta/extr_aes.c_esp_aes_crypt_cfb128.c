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
 int ESP_AES_DECRYPT ; 
 int /*<<< orphan*/  ESP_AES_ENCRYPT ; 
 int /*<<< orphan*/  esp_aes_acquire_hardware () ; 
 int /*<<< orphan*/  esp_aes_block (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  esp_aes_release_hardware () ; 
 int /*<<< orphan*/  esp_aes_setkey_hardware (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int esp_aes_crypt_cfb128( esp_aes_context *ctx,
                          int mode,
                          size_t length,
                          size_t *iv_off,
                          unsigned char iv[16],
                          const unsigned char *input,
                          unsigned char *output )
{
    int c;
    size_t n = *iv_off;

    esp_aes_acquire_hardware();

    esp_aes_setkey_hardware(ctx, ESP_AES_ENCRYPT);

    if ( mode == ESP_AES_DECRYPT ) {
        while ( length-- ) {
            if ( n == 0 ) {
                esp_aes_block(iv, iv );
            }

            c = *input++;
            *output++ = (unsigned char)( c ^ iv[n] );
            iv[n] = (unsigned char) c;

            n = ( n + 1 ) & 0x0F;
        }
    } else {
        while ( length-- ) {
            if ( n == 0 ) {
                esp_aes_block(iv, iv );
            }

            iv[n] = *output++ = (unsigned char)( iv[n] ^ *input++ );

            n = ( n + 1 ) & 0x0F;
        }
    }

    *iv_off = n;

    esp_aes_release_hardware();

    return 0;
}
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
 int ESP_AES_ENCRYPT ; 
 int /*<<< orphan*/  esp_aes_acquire_hardware () ; 
 int /*<<< orphan*/  esp_aes_block (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  esp_aes_release_hardware () ; 
 int /*<<< orphan*/  esp_aes_setkey_hardware (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

int esp_aes_crypt_cfb8( esp_aes_context *ctx,
                        int mode,
                        size_t length,
                        unsigned char iv[16],
                        const unsigned char *input,
                        unsigned char *output )
{
    unsigned char c;
    unsigned char ov[17];

    esp_aes_acquire_hardware();

    esp_aes_setkey_hardware(ctx, ESP_AES_ENCRYPT);

    while ( length-- ) {
        memcpy( ov, iv, 16 );
        esp_aes_block(iv, iv);

        if ( mode == ESP_AES_DECRYPT ) {
            ov[16] = *input;
        }

        c = *output++ = (unsigned char)( iv[0] ^ *input++ );

        if ( mode == ESP_AES_ENCRYPT ) {
            ov[16] = c;
        }

        memcpy( iv, ov + 1, 16 );
    }

    esp_aes_release_hardware();

    return 0;
}
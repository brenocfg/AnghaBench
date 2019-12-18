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
struct TYPE_3__ {unsigned int key_bytes; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ esp_aes_context ;

/* Variables and functions */
 int MBEDTLS_ERR_AES_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 

int esp_aes_setkey( esp_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits )
{
    if (keybits != 128 && keybits != 192 && keybits != 256) {
        return MBEDTLS_ERR_AES_INVALID_KEY_LENGTH;
    }
    ctx->key_bytes = keybits / 8;
    memcpy(ctx->key, key, ctx->key_bytes);
    return 0;
}
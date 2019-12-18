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
typedef  unsigned int uint32_t ;
struct TYPE_3__ {int key_bytes; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ esp_aes_context ;

/* Variables and functions */
 scalar_t__ AES_KEY_BASE ; 
 int /*<<< orphan*/  AES_MODE_REG ; 
 int ESP_AES_ENCRYPT ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void esp_aes_setkey_hardware( esp_aes_context *ctx, int mode)
{
    const uint32_t MODE_DECRYPT_BIT = 4;
    unsigned mode_reg_base = (mode == ESP_AES_ENCRYPT) ? 0 : MODE_DECRYPT_BIT;

    memcpy((uint32_t *)AES_KEY_BASE, ctx->key, ctx->key_bytes);
    REG_WRITE(AES_MODE_REG, mode_reg_base + ((ctx->key_bytes / 8) - 2));
}
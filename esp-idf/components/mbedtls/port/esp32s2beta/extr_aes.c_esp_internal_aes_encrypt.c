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
 int /*<<< orphan*/  esp_aes_block (unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  esp_aes_release_hardware () ; 
 int /*<<< orphan*/  esp_aes_setkey_hardware (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int esp_internal_aes_encrypt( esp_aes_context *ctx,
                      const unsigned char input[16],
                      unsigned char output[16] )
{
    esp_aes_acquire_hardware();
    esp_aes_setkey_hardware(ctx, ESP_AES_ENCRYPT);
    esp_aes_block(input, output);
    esp_aes_release_hardware();
    return 0;
}
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
 int /*<<< orphan*/  esp_internal_aes_encrypt (int /*<<< orphan*/ *,unsigned char const*,unsigned char*) ; 

void esp_aes_encrypt( esp_aes_context *ctx,
        const unsigned char input[16],
        unsigned char output[16] )
{
    esp_internal_aes_encrypt(ctx, input, output);
}
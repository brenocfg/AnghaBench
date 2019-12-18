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
struct TYPE_3__ {int key_bytes; } ;
typedef  TYPE_1__ esp_aes_context ;

/* Variables and functions */

__attribute__((used)) static inline bool valid_key_length(const esp_aes_context *ctx)
{
    return ctx->key_bytes == 128/8 || ctx->key_bytes == 192/8 || ctx->key_bytes == 256/8;
}
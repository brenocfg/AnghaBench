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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ AVXTEA ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB32 (int /*<<< orphan*/  const*) ; 

void av_xtea_init(AVXTEA *ctx, const uint8_t key[16])
{
    int i;

    for (i = 0; i < 4; i++)
        ctx->key[i] = AV_RB32(key + (i << 2));
}
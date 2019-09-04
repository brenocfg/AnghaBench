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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVXTEA ;

/* Variables and functions */
 int /*<<< orphan*/  xtea_crypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtea_crypt_ecb ; 

void av_xtea_crypt(AVXTEA *ctx, uint8_t *dst, const uint8_t *src, int count,
                   uint8_t *iv, int decrypt)
{
    xtea_crypt(ctx, dst, src, count, iv, decrypt, xtea_crypt_ecb);
}
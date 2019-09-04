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
typedef  int /*<<< orphan*/  AVDES ;

/* Variables and functions */
 int /*<<< orphan*/  av_des_crypt_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void av_des_crypt(AVDES *d, uint8_t *dst, const uint8_t *src,
                  int count, uint8_t *iv, int decrypt)
{
    av_des_crypt_mac(d, dst, src, count, iv, decrypt, 0);
}
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
typedef  int /*<<< orphan*/  AVHMAC ;

/* Variables and functions */
 int av_hmac_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  av_hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  av_hmac_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

int av_hmac_calc(AVHMAC *c, const uint8_t *data, unsigned int len,
                 const uint8_t *key, unsigned int keylen,
                 uint8_t *out, unsigned int outlen)
{
    av_hmac_init(c, key, keylen);
    av_hmac_update(c, data, len);
    return av_hmac_final(c, out, outlen);
}
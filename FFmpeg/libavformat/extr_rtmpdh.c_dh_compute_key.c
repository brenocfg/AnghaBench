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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  p; int /*<<< orphan*/  priv_key; } ;
typedef  TYPE_1__ FF_DH ;
typedef  int /*<<< orphan*/  FFBigNum ;

/* Variables and functions */
 int /*<<< orphan*/  bn_bn2bin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bn_free (int /*<<< orphan*/ ) ; 
 int bn_modexp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dh_compute_key(FF_DH *dh, FFBigNum pub_key_bn,
                          uint32_t secret_key_len, uint8_t *secret_key)
{
    FFBigNum k;
    int ret;

    bn_new(k);
    if (!k)
        return -1;

    if ((ret = bn_modexp(k, pub_key_bn, dh->priv_key, dh->p)) < 0) {
        bn_free(k);
        return ret;
    }
    bn_bn2bin(k, secret_key, secret_key_len);
    bn_free(k);

    /* return the length of the shared secret key like DH_compute_key */
    return secret_key_len;
}
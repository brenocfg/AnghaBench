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
typedef  int /*<<< orphan*/ * FFBigNum ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  bn_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bn_cmp_1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_free (int /*<<< orphan*/ *) ; 
 int bn_modexp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bn_sub_word (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dh_is_valid_public_key(FFBigNum y, FFBigNum p, FFBigNum q)
{
    FFBigNum bn = NULL;
    int ret = AVERROR(EINVAL);

    bn_new(bn);
    if (!bn)
        return AVERROR(ENOMEM);

    /* y must lie in [2, p - 1] */
    bn_set_word(bn, 1);
    if (!bn_cmp(y, bn))
        goto fail;

    /* bn = p - 2 */
    bn_copy(bn, p);
    bn_sub_word(bn, 1);
    if (!bn_cmp(y, bn))
        goto fail;

    /* Verify with Sophie-Germain prime
     *
     * This is a nice test to make sure the public key position is calculated
     * correctly. This test will fail in about 50% of the cases if applied to
     * random data.
     */
    /* y must fulfill y^q mod p = 1 */
    if ((ret = bn_modexp(bn, y, q, p)) < 0)
        goto fail;

    ret = AVERROR(EINVAL);
    if (bn_cmp_1(bn))
        goto fail;

    ret = 0;
fail:
    bn_free(bn);

    return ret;
}
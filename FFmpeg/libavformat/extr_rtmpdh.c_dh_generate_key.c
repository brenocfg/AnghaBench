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
struct TYPE_3__ {int /*<<< orphan*/ * pub_key; int /*<<< orphan*/  p; int /*<<< orphan*/ * priv_key; int /*<<< orphan*/  g; } ;
typedef  TYPE_1__ FF_DH ;
typedef  int /*<<< orphan*/ * FFBigNum ;

/* Variables and functions */
 int MAX_BYTES ; 
 int /*<<< orphan*/  bn_free (int /*<<< orphan*/ *) ; 
 scalar_t__ bn_modexp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_new (int /*<<< orphan*/ *) ; 
 int bn_num_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_random (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static FFBigNum dh_generate_key(FF_DH *dh)
{
    int num_bytes;

    num_bytes = bn_num_bytes(dh->p) - 1;
    if (num_bytes <= 0 || num_bytes > MAX_BYTES)
        return NULL;

    bn_new(dh->priv_key);
    if (!dh->priv_key)
        return NULL;
    bn_random(dh->priv_key, 8 * num_bytes);

    bn_new(dh->pub_key);
    if (!dh->pub_key) {
        bn_free(dh->priv_key);
        return NULL;
    }

    if (bn_modexp(dh->pub_key, dh->g, dh->priv_key, dh->p) < 0)
        return NULL;

    return dh->pub_key;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ccmode_ecb {int /*<<< orphan*/  (* ecb ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * dec; int /*<<< orphan*/ * enc; } ;
typedef  TYPE_1__ des_ecb_key_schedule ;
typedef  int /*<<< orphan*/  des_cblock ;
typedef  int /*<<< orphan*/  ccecb_ctx ;
struct TYPE_5__ {struct ccmode_ecb* ccdes_ecb_decrypt; struct ccmode_ecb* ccdes_ecb_encrypt; } ;

/* Variables and functions */
 TYPE_2__* g_crypto_funcs ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void des_ecb_encrypt(des_cblock *in, des_cblock *out, des_ecb_key_schedule *ks, int enc)
{
	const struct ccmode_ecb *ecb = enc ? g_crypto_funcs->ccdes_ecb_encrypt : g_crypto_funcs->ccdes_ecb_decrypt;
	ccecb_ctx *ctx = enc ? ks->enc : ks->dec;

	ecb->ecb(ctx, 1, in, out);
}
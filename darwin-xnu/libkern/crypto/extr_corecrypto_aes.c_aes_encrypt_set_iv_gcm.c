#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ccmode_gcm {int dummy; } ;
typedef  int /*<<< orphan*/  ccgcm_ctx ;
typedef  int /*<<< orphan*/  aes_rval ;
struct TYPE_2__ {struct ccmode_gcm* ccaes_gcm_encrypt; } ;

/* Variables and functions */
 int /*<<< orphan*/  aes_error ; 
 int /*<<< orphan*/  ccgcm_set_iv (struct ccmode_gcm const*,int /*<<< orphan*/ *,unsigned int,unsigned char const*) ; 
 TYPE_1__* g_crypto_funcs ; 

aes_rval aes_encrypt_set_iv_gcm(const unsigned char *in_iv, unsigned int len, ccgcm_ctx *ctx)
{
	const struct ccmode_gcm *gcm = g_crypto_funcs->ccaes_gcm_encrypt;
	if (!gcm) {
	        return aes_error;
	}

	return ccgcm_set_iv(gcm, ctx, len, in_iv);
}
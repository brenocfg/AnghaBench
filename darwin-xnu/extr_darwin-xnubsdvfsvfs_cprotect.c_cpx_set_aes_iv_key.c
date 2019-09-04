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
struct cpx {int /*<<< orphan*/  cpx_flags; int /*<<< orphan*/  cpx_iv_aes_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CPX_IV_AES_CTX_INITIALIZED ; 
 int /*<<< orphan*/  CPX_IV_AES_CTX_VFS ; 
 int CPX_USE_OFFSET_FOR_IV ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aes_encrypt_key128 (void*,int /*<<< orphan*/ *) ; 

void cpx_set_aes_iv_key(struct cpx *cpx, void *iv_key)
{
	aes_encrypt_key128(iv_key, &cpx->cpx_iv_aes_ctx);
	SET(cpx->cpx_flags, CPX_IV_AES_CTX_INITIALIZED | CPX_USE_OFFSET_FOR_IV);
	CLR(cpx->cpx_flags, CPX_IV_AES_CTX_VFS);
}
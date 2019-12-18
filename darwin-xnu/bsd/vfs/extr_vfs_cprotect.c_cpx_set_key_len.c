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
typedef  int /*<<< orphan*/  uint16_t ;
struct cpx {int /*<<< orphan*/  cpx_flags; int /*<<< orphan*/  cpx_key_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int) ; 
 int CPX_IV_AES_CTX_INITIALIZED ; 
 int CPX_IV_AES_CTX_VFS ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int) ; 

void cpx_set_key_len(struct cpx *cpx, uint16_t key_len)
{
	cpx->cpx_key_len = key_len;

	if (ISSET(cpx->cpx_flags, CPX_IV_AES_CTX_VFS)) {
		/*
		 * We assume that if the key length is being modified, the key
		 * has changed.  As a result, un-set any bits related to the
		 * AES context, if needed. They should be re-generated
		 * on-demand.
		 */
		CLR(cpx->cpx_flags, CPX_IV_AES_CTX_INITIALIZED | CPX_IV_AES_CTX_VFS);
	}
}
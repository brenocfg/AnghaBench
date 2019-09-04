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
typedef  TYPE_1__* cpx_t ;
struct TYPE_3__ {int cpx_max_key_len; scalar_t__ cpx_key_len; scalar_t__ cpx_flags; int /*<<< orphan*/  cpx_iv_aes_ctx; int /*<<< orphan*/ * cpx_cached_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

void cpx_flush(cpx_t cpx)
{
	bzero(cpx->cpx_cached_key, cpx->cpx_max_key_len);
	bzero(&cpx->cpx_iv_aes_ctx, sizeof(cpx->cpx_iv_aes_ctx));
	cpx->cpx_flags = 0;
	cpx->cpx_key_len = 0;
}
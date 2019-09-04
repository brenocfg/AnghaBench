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
struct ccmode_cbc {int dummy; } ;
typedef  int /*<<< orphan*/  cccbc_iv ;
typedef  int /*<<< orphan*/  cccbc_ctx ;
struct TYPE_2__ {size_t (* ccpad_cts3_decrypt_fn ) (struct ccmode_cbc const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,void const*,void*) ;} ;

/* Variables and functions */
 TYPE_1__* g_crypto_funcs ; 
 size_t stub1 (struct ccmode_cbc const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,void const*,void*) ; 

size_t
ccpad_cts3_decrypt(const struct ccmode_cbc *cbc, cccbc_ctx *cbc_key,
		   cccbc_iv *iv, size_t nbytes, const void *in, void *out)
{
	if (g_crypto_funcs)
		return (*g_crypto_funcs->ccpad_cts3_decrypt_fn)(cbc, cbc_key, iv, nbytes, in, out);
	return (0);
}
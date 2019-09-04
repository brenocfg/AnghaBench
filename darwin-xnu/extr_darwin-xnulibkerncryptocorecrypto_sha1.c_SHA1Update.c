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
struct ccdigest_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ccdigest_update_fn ) (struct ccdigest_info const*,int /*<<< orphan*/ ,size_t,void const*) ;struct ccdigest_info* ccsha1_di; } ;
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  DiToSHA1 (struct ccdigest_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1ToDi (struct ccdigest_info const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccdigest_di_decl (struct ccdigest_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  di_ctx ; 
 TYPE_1__* g_crypto_funcs ; 
 int /*<<< orphan*/  stub1 (struct ccdigest_info const*,int /*<<< orphan*/ ,size_t,void const*) ; 

void SHA1Update(SHA1_CTX *ctx, const void *data, size_t len)
{
	const struct ccdigest_info *di=g_crypto_funcs->ccsha1_di;
	ccdigest_di_decl(di, di_ctx);
	
	SHA1ToDi(di, ctx, di_ctx);
	g_crypto_funcs->ccdigest_update_fn(di, di_ctx, len, data);	
	DiToSHA1(di, di_ctx, ctx);
}
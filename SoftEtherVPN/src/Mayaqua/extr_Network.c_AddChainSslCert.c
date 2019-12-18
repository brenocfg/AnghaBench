#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ssl_ctx_st {int dummy; } ;
struct TYPE_6__ {int do_not_free; int /*<<< orphan*/  x509; } ;
typedef  TYPE_1__ X ;

/* Variables and functions */
 TYPE_1__* CloneX (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeX (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_CTX_add_extra_chain_cert (struct ssl_ctx_st*,int /*<<< orphan*/ ) ; 

bool AddChainSslCert(struct ssl_ctx_st *ctx, X *x)
{
	bool ret = false;
	X *x_copy;
	// Validate arguments
	if (ctx == NULL || x == NULL)
	{
		return ret;
	}

	x_copy = CloneX(x);

	if (x_copy != NULL)
	{
		SSL_CTX_add_extra_chain_cert(ctx, x_copy->x509);
		x_copy->do_not_free = true;

		ret = true;

		FreeX(x_copy);
	}

	return ret;
}
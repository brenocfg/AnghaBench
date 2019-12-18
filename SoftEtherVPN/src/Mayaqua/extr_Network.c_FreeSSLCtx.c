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
struct ssl_ctx_st {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (struct ssl_ctx_st*) ; 

void FreeSSLCtx(struct ssl_ctx_st *ctx)
{
	// Validate arguments
	if (ctx == NULL)
	{
		return;
	}

	SSL_CTX_free(ctx);
}
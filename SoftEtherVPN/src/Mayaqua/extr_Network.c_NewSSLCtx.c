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
 struct ssl_ctx_st* SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_ecdh_auto (struct ssl_ctx_st*,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (struct ssl_ctx_st*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_tmp_dh_callback (struct ssl_ctx_st*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_OP_CIPHER_SERVER_PREFERENCE ; 
 int /*<<< orphan*/  SSL_OP_NO_TICKET ; 
 int /*<<< orphan*/  SSLv23_method () ; 
 int /*<<< orphan*/  TmpDhCallback ; 

struct ssl_ctx_st *NewSSLCtx(bool server_mode)
{
	struct ssl_ctx_st *ctx = SSL_CTX_new(SSLv23_method());

#ifdef	SSL_OP_NO_TICKET
	SSL_CTX_set_options(ctx, SSL_OP_NO_TICKET);
#endif	// SSL_OP_NO_TICKET

#ifdef	SSL_OP_CIPHER_SERVER_PREFERENCE
	if (server_mode)
	{
		SSL_CTX_set_options(ctx, SSL_OP_CIPHER_SERVER_PREFERENCE);
	}
#endif	// SSL_OP_CIPHER_SERVER_PREFERENCE

	SSL_CTX_set_tmp_dh_callback(ctx, TmpDhCallback);

#ifdef	SSL_CTX_set_ecdh_auto
	SSL_CTX_set_ecdh_auto(ctx, 1);
#endif	// SSL_CTX_set_ecdh_auto

	return ctx;
}
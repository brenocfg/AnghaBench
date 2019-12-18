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
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int SSL_CTX_check_private_key (int /*<<< orphan*/ *) ; 
 int SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  ssl_errstr () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static int
init_cert_file(SSL_CTX *ctx, const char *path)
{
	int error;

	/* Load certificate into ctx */
	error = SSL_CTX_use_certificate_chain_file(ctx, path);
	if (error < 1) {
		syslog(LOG_ERR, "SSL: Cannot load certificate `%s': %s", path, ssl_errstr());
		return (-1);
	}

	/* Add private key to ctx */
	error = SSL_CTX_use_PrivateKey_file(ctx, path, SSL_FILETYPE_PEM);
	if (error < 1) {
		syslog(LOG_ERR, "SSL: Cannot load private key `%s': %s", path, ssl_errstr());
		return (-1);
	}

	/*
	 * Check the consistency of a private key with the corresponding
         * certificate
	 */
	error = SSL_CTX_check_private_key(ctx);
	if (error < 1) {
		syslog(LOG_ERR, "SSL: Cannot check private key: %s", ssl_errstr());
		return (-1);
	}

	return (0);
}
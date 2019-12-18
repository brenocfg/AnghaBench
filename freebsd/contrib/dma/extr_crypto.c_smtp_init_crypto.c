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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_2__ {int /*<<< orphan*/ * ssl; int /*<<< orphan*/  features; int /*<<< orphan*/ * certfile; } ;
typedef  int /*<<< orphan*/  SSL_METHOD ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  NOSSL ; 
 int SECURETRANS ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ *) ; 
 int SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 int SSL_set_fd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SSLv23_client_method () ; 
 int STARTTLS ; 
 int TLS_OPP ; 
 int /*<<< orphan*/ * TLS_client_method () ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  hostname () ; 
 int init_cert_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neterr ; 
 int read_remote (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_remote_command (int,char*,...) ; 
 int /*<<< orphan*/  ssl_errstr () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

int
smtp_init_crypto(int fd, int feature)
{
	SSL_CTX *ctx = NULL;
#if (OPENSSL_VERSION_NUMBER >= 0x00909000L)
	const SSL_METHOD *meth = NULL;
#else
	SSL_METHOD *meth = NULL;
#endif
	X509 *cert;
	int error;

	/* XXX clean up on error/close */
	/* Init SSL library */
	SSL_library_init();
	SSL_load_error_strings();

	// Allow any possible version
#if (OPENSSL_VERSION_NUMBER >= 0x10100000L)
	meth = TLS_client_method();
#else
	meth = SSLv23_client_method();
#endif

	ctx = SSL_CTX_new(meth);
	if (ctx == NULL) {
		syslog(LOG_WARNING, "remote delivery deferred: SSL init failed: %s", ssl_errstr());
		return (1);
	}

	/* User supplied a certificate */
	if (config.certfile != NULL) {
		error = init_cert_file(ctx, config.certfile);
		if (error) {
			syslog(LOG_WARNING, "remote delivery deferred");
			return (1);
		}
	}

	/*
	 * If the user wants STARTTLS, we have to send EHLO here
	 */
	if (((feature & SECURETRANS) != 0) &&
	     (feature & STARTTLS) != 0) {
		/* TLS init phase, disable SSL_write */
		config.features |= NOSSL;

		send_remote_command(fd, "EHLO %s", hostname());
		if (read_remote(fd, 0, NULL) == 2) {
			send_remote_command(fd, "STARTTLS");
			if (read_remote(fd, 0, NULL) != 2) {
				if ((feature & TLS_OPP) == 0) {
					syslog(LOG_ERR, "remote delivery deferred: STARTTLS not available: %s", neterr);
					return (1);
				} else {
					syslog(LOG_INFO, "in opportunistic TLS mode, STARTTLS not available: %s", neterr);
					return (0);
				}
			}
		}
		/* End of TLS init phase, enable SSL_write/read */
		config.features &= ~NOSSL;
	}

	config.ssl = SSL_new(ctx);
	if (config.ssl == NULL) {
		syslog(LOG_NOTICE, "remote delivery deferred: SSL struct creation failed: %s",
		       ssl_errstr());
		return (1);
	}

	/* Set ssl to work in client mode */
	SSL_set_connect_state(config.ssl);

	/* Set fd for SSL in/output */
	error = SSL_set_fd(config.ssl, fd);
	if (error == 0) {
		syslog(LOG_NOTICE, "remote delivery deferred: SSL set fd failed: %s",
		       ssl_errstr());
		return (1);
	}

	/* Open SSL connection */
	error = SSL_connect(config.ssl);
	if (error < 0) {
		syslog(LOG_ERR, "remote delivery deferred: SSL handshake failed fatally: %s",
		       ssl_errstr());
		return (1);
	}

	/* Get peer certificate */
	cert = SSL_get_peer_certificate(config.ssl);
	if (cert == NULL) {
		syslog(LOG_WARNING, "remote delivery deferred: Peer did not provide certificate: %s",
		       ssl_errstr());
	}
	X509_free(cert);

	return (0);
}
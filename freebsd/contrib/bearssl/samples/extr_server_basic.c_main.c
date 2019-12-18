#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  br_sslio_context ;
struct TYPE_12__ {int /*<<< orphan*/  eng; } ;
typedef  TYPE_1__ br_ssl_server_context ;

/* Variables and functions */
 int /*<<< orphan*/  BR_KEYTYPE_EC ; 
 int /*<<< orphan*/  BR_KEYTYPE_RSA ; 
 int BR_SSL_BUFSIZE_BIDI ; 
 int /*<<< orphan*/  CHAIN ; 
 int /*<<< orphan*/  CHAIN_LEN ; 
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  HTTP_RES ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SKEY ; 
 int accept_client (int) ; 
 int br_ssl_engine_last_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_buffer (int /*<<< orphan*/ *,unsigned char*,int,int) ; 
 int /*<<< orphan*/  br_ssl_server_init_full_ec (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_server_init_full_rsa (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_server_init_mine2c (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_server_init_mine2g (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_server_init_minf2c (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_server_init_minf2g (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_server_init_minr2g (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_server_init_minu2g (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_server_init_minv2g (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_server_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  br_sslio_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_sslio_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ br_sslio_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  br_sslio_write_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int host_bind (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_read ; 
 int /*<<< orphan*/  sock_write ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	const char *port;
	int fd;

	if (argc != 2) {
		return EXIT_FAILURE;
	}
	port = argv[1];

	/*
	 * Ignore SIGPIPE to avoid crashing in case of abrupt socket close.
	 */
	signal(SIGPIPE, SIG_IGN);

	/*
	 * Open the server socket.
	 */
	fd = host_bind(NULL, port);
	if (fd < 0) {
		return EXIT_FAILURE;
	}

	/*
	 * Process each client, one at a time.
	 */
	for (;;) {
		int cfd;
		br_ssl_server_context sc;
		unsigned char iobuf[BR_SSL_BUFSIZE_BIDI];
		br_sslio_context ioc;
		int lcwn, err;

		cfd = accept_client(fd);
		if (cfd < 0) {
			return EXIT_FAILURE;
		}

		/*
		 * Initialise the context with the cipher suites and
		 * algorithms. This depends on the server key type
		 * (and, for EC keys, the signature algorithm used by
		 * the CA to sign the server's certificate).
		 *
		 * Depending on the defined macros, we may select one of
		 * the "minimal" profiles. Key exchange algorithm depends
		 * on the key type:
		 *   RSA key: RSA or ECDHE_RSA
		 *   EC key, cert signed with ECDSA: ECDH_ECDSA or ECDHE_ECDSA
		 *   EC key, cert signed with RSA: ECDH_RSA or ECDHE_ECDSA
		 */
#if SERVER_RSA
#if SERVER_PROFILE_MIN_FS
#if SERVER_CHACHA20
		br_ssl_server_init_mine2c(&sc, CHAIN, CHAIN_LEN, &SKEY);
#else
		br_ssl_server_init_mine2g(&sc, CHAIN, CHAIN_LEN, &SKEY);
#endif
#elif SERVER_PROFILE_MIN_NOFS
		br_ssl_server_init_minr2g(&sc, CHAIN, CHAIN_LEN, &SKEY);
#else
		br_ssl_server_init_full_rsa(&sc, CHAIN, CHAIN_LEN, &SKEY);
#endif
#elif SERVER_EC
#if SERVER_PROFILE_MIN_FS
#if SERVER_CHACHA20
		br_ssl_server_init_minf2c(&sc, CHAIN, CHAIN_LEN, &SKEY);
#else
		br_ssl_server_init_minf2g(&sc, CHAIN, CHAIN_LEN, &SKEY);
#endif
#elif SERVER_PROFILE_MIN_NOFS
		br_ssl_server_init_minv2g(&sc, CHAIN, CHAIN_LEN, &SKEY);
#else
		br_ssl_server_init_full_ec(&sc, CHAIN, CHAIN_LEN,
			BR_KEYTYPE_EC, &SKEY);
#endif
#else /* SERVER_MIXED */
#if SERVER_PROFILE_MIN_FS
#if SERVER_CHACHA20
		br_ssl_server_init_minf2c(&sc, CHAIN, CHAIN_LEN, &SKEY);
#else
		br_ssl_server_init_minf2g(&sc, CHAIN, CHAIN_LEN, &SKEY);
#endif
#elif SERVER_PROFILE_MIN_NOFS
		br_ssl_server_init_minu2g(&sc, CHAIN, CHAIN_LEN, &SKEY);
#else
		br_ssl_server_init_full_ec(&sc, CHAIN, CHAIN_LEN,
			BR_KEYTYPE_RSA, &SKEY);
#endif
#endif
		/*
		 * Set the I/O buffer to the provided array. We
		 * allocated a buffer large enough for full-duplex
		 * behaviour with all allowed sizes of SSL records,
		 * hence we set the last argument to 1 (which means
		 * "split the buffer into separate input and output
		 * areas").
		 */
		br_ssl_engine_set_buffer(&sc.eng, iobuf, sizeof iobuf, 1);

		/*
		 * Reset the server context, for a new handshake.
		 */
		br_ssl_server_reset(&sc);

		/*
		 * Initialise the simplified I/O wrapper context.
		 */
		br_sslio_init(&ioc, &sc.eng, sock_read, &cfd, sock_write, &cfd);

		/*
		 * Read bytes until two successive LF (or CR+LF) are received.
		 */
		lcwn = 0;
		for (;;) {
			unsigned char x;

			if (br_sslio_read(&ioc, &x, 1) < 0) {
				goto client_drop;
			}
			if (x == 0x0D) {
				continue;
			}
			if (x == 0x0A) {
				if (lcwn) {
					break;
				}
				lcwn = 1;
			} else {
				lcwn = 0;
			}
		}

		/*
		 * Write a response and close the connection.
		 */
		br_sslio_write_all(&ioc, HTTP_RES, strlen(HTTP_RES));
		br_sslio_close(&ioc);

	client_drop:
		err = br_ssl_engine_last_error(&sc.eng);
		if (err == 0) {
			fprintf(stderr, "SSL closed (correctly).\n");
		} else {
			fprintf(stderr, "SSL error: %d\n", err);
		}
		close(cfd);
	}
}
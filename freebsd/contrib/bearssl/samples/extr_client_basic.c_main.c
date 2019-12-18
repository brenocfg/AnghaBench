#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  br_x509_minimal_context ;
typedef  int /*<<< orphan*/  br_sslio_context ;
struct TYPE_4__ {int /*<<< orphan*/  eng; } ;
typedef  TYPE_1__ br_ssl_client_context ;

/* Variables and functions */
 int BR_SSL_BUFSIZE_BIDI ; 
 scalar_t__ BR_SSL_CLOSED ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  TAs ; 
 int /*<<< orphan*/  TAs_NUM ; 
 int /*<<< orphan*/  br_ssl_client_init_full (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ssl_client_reset (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ br_ssl_engine_current_state (int /*<<< orphan*/ *) ; 
 int br_ssl_engine_last_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_buffer (int /*<<< orphan*/ *,unsigned char*,int,int) ; 
 int /*<<< orphan*/  br_sslio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_sslio_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int br_sslio_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  br_sslio_write_all (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int host_connect (char const*,char const*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_read ; 
 int /*<<< orphan*/  sock_write ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char const*) ; 

int
main(int argc, char *argv[])
{
	const char *host, *port, *path;
	int fd;
	br_ssl_client_context sc;
	br_x509_minimal_context xc;
	unsigned char iobuf[BR_SSL_BUFSIZE_BIDI];
	br_sslio_context ioc;

	/*
	 * Parse command-line argument: host, port, and path. The path
	 * is optional; if absent, "/" is used.
	 */
	if (argc < 3 || argc > 4) {
		return EXIT_FAILURE;
	}
	host = argv[1];
	port = argv[2];
	if (argc == 4) {
		path = argv[3];
	} else {
		path = "/";
	}

	/*
	 * Ignore SIGPIPE to avoid crashing in case of abrupt socket close.
	 */
	signal(SIGPIPE, SIG_IGN);

	/*
	 * Open the socket to the target server.
	 */
	fd = host_connect(host, port);
	if (fd < 0) {
		return EXIT_FAILURE;
	}

	/*
	 * Initialise the client context:
	 * -- Use the "full" profile (all supported algorithms).
	 * -- The provided X.509 validation engine is initialised, with
	 *    the hardcoded trust anchor.
	 */
	br_ssl_client_init_full(&sc, &xc, TAs, TAs_NUM);

	/*
	 * Set the I/O buffer to the provided array. We allocated a
	 * buffer large enough for full-duplex behaviour with all
	 * allowed sizes of SSL records, hence we set the last argument
	 * to 1 (which means "split the buffer into separate input and
	 * output areas").
	 */
	br_ssl_engine_set_buffer(&sc.eng, iobuf, sizeof iobuf, 1);

	/*
	 * Reset the client context, for a new handshake. We provide the
	 * target host name: it will be used for the SNI extension. The
	 * last parameter is 0: we are not trying to resume a session.
	 */
	br_ssl_client_reset(&sc, host, 0);

	/*
	 * Initialise the simplified I/O wrapper context, to use our
	 * SSL client context, and the two callbacks for socket I/O.
	 */
	br_sslio_init(&ioc, &sc.eng, sock_read, &fd, sock_write, &fd);

	/*
	 * Note that while the context has, at that point, already
	 * assembled the ClientHello to send, nothing happened on the
	 * network yet. Real I/O will occur only with the next call.
	 *
	 * We write our simple HTTP request. We could test each call
	 * for an error (-1), but this is not strictly necessary, since
	 * the error state "sticks": if the context fails for any reason
	 * (e.g. bad server certificate), then it will remain in failed
	 * state and all subsequent calls will return -1 as well.
	 */
	br_sslio_write_all(&ioc, "GET ", 4);
	br_sslio_write_all(&ioc, path, strlen(path));
	br_sslio_write_all(&ioc, " HTTP/1.0\r\nHost: ", 17);
	br_sslio_write_all(&ioc, host, strlen(host));
	br_sslio_write_all(&ioc, "\r\n\r\n", 4);

	/*
	 * SSL is a buffered protocol: we make sure that all our request
	 * bytes are sent onto the wire.
	 */
	br_sslio_flush(&ioc);

	/*
	 * Read the server's response. We use here a small 512-byte buffer,
	 * but most of the buffering occurs in the client context: the
	 * server will send full records (up to 16384 bytes worth of data
	 * each), and the client context buffers one full record at a time.
	 */
	for (;;) {
		int rlen;
		unsigned char tmp[512];

		rlen = br_sslio_read(&ioc, tmp, sizeof tmp);
		if (rlen < 0) {
			break;
		}
		fwrite(tmp, 1, rlen, stdout);
	}

	/*
	 * Close the socket.
	 */
	close(fd);

	/*
	 * Check whether we closed properly or not. If the engine is
	 * closed, then its error status allows to distinguish between
	 * a normal closure and a SSL error.
	 *
	 * If the engine is NOT closed, then this means that the
	 * underlying network socket was closed or failed in some way.
	 * Note that many Web servers out there do not properly close
	 * their SSL connections (they don't send a close_notify alert),
	 * which will be reported here as "socket closed without proper
	 * SSL termination".
	 */
	if (br_ssl_engine_current_state(&sc.eng) == BR_SSL_CLOSED) {
		int err;

		err = br_ssl_engine_last_error(&sc.eng);
		if (err == 0) {
			fprintf(stderr, "closed.\n");
			return EXIT_SUCCESS;
		} else {
			fprintf(stderr, "SSL error %d\n", err);
			return EXIT_FAILURE;
		}
	} else {
		fprintf(stderr,
			"socket closed without proper SSL termination\n");
		return EXIT_FAILURE;
	}
}
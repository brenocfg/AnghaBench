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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage_client(void)
{
	fprintf(stderr,
"usage: brssl client server[:port] [ options ]\n");
	fprintf(stderr,
"options:\n");
	fprintf(stderr,
"   -q              suppress verbose messages\n");
	fprintf(stderr,
"   -trace          activate extra debug messages (dump of all packets)\n");
	fprintf(stderr,
"   -sni name       use this specific name for SNI\n");
	fprintf(stderr,
"   -nosni          do not send any SNI\n");
	fprintf(stderr,
"   -mono           use monodirectional buffering\n");
	fprintf(stderr,
"   -buf length     set the I/O buffer length (in bytes)\n");
	fprintf(stderr,
"   -CA file        add certificates in 'file' to trust anchors\n");
	fprintf(stderr,
"   -cert file      set client certificate chain\n");
	fprintf(stderr,
"   -key file       set client private key (for certificate authentication)\n");
	fprintf(stderr,
"   -nostaticecdh   prohibit full-static ECDH (client certificate)\n");
	fprintf(stderr,
"   -list           list supported names (protocols, algorithms...)\n");
	fprintf(stderr,
"   -vmin name      set minimum supported version (default: TLS-1.0)\n");
	fprintf(stderr,
"   -vmax name      set maximum supported version (default: TLS-1.2)\n");
	fprintf(stderr,
"   -cs names       set list of supported cipher suites (comma-separated)\n");
	fprintf(stderr,
"   -hf names       add support for some hash functions (comma-separated)\n");
	fprintf(stderr,
"   -minhello len   set minimum ClientHello length (in bytes)\n");
	fprintf(stderr,
"   -fallback       send the TLS_FALLBACK_SCSV (i.e. claim a downgrade)\n");
	fprintf(stderr,
"   -noreneg        prohibit renegotiations\n");
	fprintf(stderr,
"   -alpn name      add protocol name to list of protocols (ALPN extension)\n");
	fprintf(stderr,
"   -strictalpn     fail on ALPN mismatch\n");
}
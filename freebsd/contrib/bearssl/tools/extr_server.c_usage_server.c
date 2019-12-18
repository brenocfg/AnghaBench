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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage_server(void)
{
	fprintf(stderr,
"usage: brssl server [ options ]\n");
	fprintf(stderr,
"options:\n");
	fprintf(stderr,
"   -q              suppress verbose messages\n");
	fprintf(stderr,
"   -trace          activate extra debug messages (dump of all packets)\n");
	fprintf(stderr,
"   -b name         bind to a specific address or host name\n");
	fprintf(stderr,
"   -p port         bind to a specific port (default: 4433)\n");
	fprintf(stderr,
"   -mono           use monodirectional buffering\n");
	fprintf(stderr,
"   -buf length     set the I/O buffer length (in bytes)\n");
	fprintf(stderr,
"   -cache length   set the session cache storage length (in bytes)\n");
	fprintf(stderr,
"   -cert fname     read certificate chain from file 'fname'\n");
	fprintf(stderr,
"   -key fname      read private key from file 'fname'\n");
	fprintf(stderr,
"   -CA file        add trust anchors from 'file' (for client auth)\n");
	fprintf(stderr,
"   -anon_ok        request but do not require a client certificate\n");
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
"   -cbhash         test hashing in policy callback\n");
	fprintf(stderr,
"   -serverpref     enforce server's preferences for cipher suites\n");
	fprintf(stderr,
"   -noreneg        prohibit renegotiations\n");
	fprintf(stderr,
"   -alpn name      add protocol name to list of protocols (ALPN extension)\n");
	fprintf(stderr,
"   -strictalpn     fail on ALPN mismatch\n");
	exit(EXIT_FAILURE);
}
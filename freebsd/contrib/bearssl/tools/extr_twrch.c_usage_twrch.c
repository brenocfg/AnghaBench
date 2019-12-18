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
usage_twrch(void)
{
	fprintf(stderr,
"usage: brssl twrch [ options ]\n");
	fprintf(stderr,
"options:\n");
	fprintf(stderr,
"   -trace          dump all packets on stderr\n");
	fprintf(stderr,
"   -v              verbose error messages on stderr\n");
	fprintf(stderr,
"   -server         act as an SSL server\n");
	fprintf(stderr,
"   -client         act as an SSL client\n");
	fprintf(stderr,
"   -sni name       use specified name for SNI\n");
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
"   -CA file        add trust anchors from 'file' (for peer auth)\n");
	fprintf(stderr,
"   -anon_ok        request but do not require a client certificate\n");
	fprintf(stderr,
"   -nostaticecdh   prohibit full-static ECDH (client only)\n");
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
"   -serverpref     enforce server's preferences for cipher suites\n");
	fprintf(stderr,
"   -noreneg        prohibit renegotiations\n");
	fprintf(stderr,
"   -alpn name      add protocol name to list of protocols (ALPN extension)\n");
	fprintf(stderr,
"   -strictalpn     fail on ALPN mismatch\n");
}
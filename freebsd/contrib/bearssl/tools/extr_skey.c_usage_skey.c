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
usage_skey(void)
{
	fprintf(stderr,
"usage: brssl skey [ options ] file...\n");
	fprintf(stderr,
"options:\n");
	fprintf(stderr,
"   -q             suppress verbose messages\n");
	fprintf(stderr,
"   -text          print private key details (human-readable)\n");
	fprintf(stderr,
"   -C             print private key details (C code)\n");
	fprintf(stderr,
"   -rawder file   save private key in 'file' (raw format, DER)\n");
	fprintf(stderr,
"   -rawpem file   save private key in 'file' (raw format, PEM)\n");
	fprintf(stderr,
"   -pk8der file   save private key in 'file' (PKCS#8 format, DER)\n");
	fprintf(stderr,
"   -pk8pem file   save private key in 'file' (PKCS#8 format, PEM)\n");
	fprintf(stderr,
"   -gen spec      generate a new key using the provided key specification\n");
	fprintf(stderr,
"   -list          list known elliptic curve names\n");
	fprintf(stderr,
"Key specification begins with a key type, followed by optional parameters\n");
	fprintf(stderr,
"that depend on the key type, separated by colon characters:\n");
	fprintf(stderr,
"   rsa[:size[:pubexep]]   RSA key (defaults: size = 2048, pubexp = 3)\n");
	fprintf(stderr,
"   ec[:curvename]         EC key (default curve: secp256r1)\n");
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* mul ) (unsigned char*,size_t,unsigned char*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ br_ec_impl ;

/* Variables and functions */
 int /*<<< orphan*/  BR_EC_secp256r1 ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  check_equals (char*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t hextobin (unsigned char*,char const*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int stub1 (unsigned char*,size_t,unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_EC_P256_carry_inner(const br_ec_impl *impl, const char *sP, const char *sQ)
{
	unsigned char P[65], Q[sizeof P], k[1];
	size_t plen, qlen;

	plen = hextobin(P, sP);
	qlen = hextobin(Q, sQ);
	if (plen != sizeof P || qlen != sizeof P) {
		fprintf(stderr, "KAT is incorrect\n");
		exit(EXIT_FAILURE);
	}
	k[0] = 0x10;
	if (impl->mul(P, plen, k, 1, BR_EC_secp256r1) != 1) {
		fprintf(stderr, "P-256 multiplication failed\n");
		exit(EXIT_FAILURE);
	}
	check_equals("P256_carry", P, Q, plen);
	printf(".");
	fflush(stdout);
}
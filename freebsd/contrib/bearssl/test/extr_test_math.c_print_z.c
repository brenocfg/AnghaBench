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
typedef  int /*<<< orphan*/  mpz_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mpz_export (unsigned char*,size_t*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_z(mpz_t z)
{
	unsigned char zb[1000];
	size_t zlen, k;

	mpz_export(zb, &zlen, 1, 1, 0, 0, z);
	if (zlen == 0) {
		printf(" 00");
		return;
	}
	if ((zlen & 3) != 0) {
		k = 4 - (zlen & 3);
		memmove(zb + k, zb, zlen);
		memset(zb, 0, k);
		zlen += k;
	}
	for (k = 0; k < zlen; k += 4) {
		printf(" %02X%02X%02X%02X",
			zb[k], zb[k + 1], zb[k + 2], zb[k + 3]);
	}
}
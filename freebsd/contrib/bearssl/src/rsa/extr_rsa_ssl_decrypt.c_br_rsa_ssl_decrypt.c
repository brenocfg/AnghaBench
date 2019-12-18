#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int n_bitlen; } ;
typedef  TYPE_1__ br_rsa_private_key ;
typedef  int /*<<< orphan*/  (* br_rsa_private ) (unsigned char*,TYPE_1__ const*) ;

/* Variables and functions */
 int /*<<< orphan*/  EQ (unsigned char,int) ; 
 int /*<<< orphan*/  NEQ (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 

uint32_t
br_rsa_ssl_decrypt(br_rsa_private core, const br_rsa_private_key *sk,
	unsigned char *data, size_t len)
{
	uint32_t x;
	size_t u;

	/*
	 * A first check on length. Since this test works only on the
	 * buffer length, it needs not (and cannot) be constant-time.
	 */
	if (len < 59 || len != (sk->n_bitlen + 7) >> 3) {
		return 0;
	}
	x = core(data, sk);

	x &= EQ(data[0], 0x00);
	x &= EQ(data[1], 0x02);
	for (u = 2; u < (len - 49); u ++) {
		x &= NEQ(data[u], 0);
	}
	x &= EQ(data[len - 49], 0x00);
	memmove(data, data + len - 48, 48);
	return x;
}
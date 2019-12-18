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
typedef  int /*<<< orphan*/  br_des_gen_cbcenc_keys ;
struct TYPE_3__ {int /*<<< orphan*/  (* run ) (void*,unsigned char*,unsigned char*,int) ;int /*<<< orphan*/  (* init ) (void*,unsigned char*,int) ;} ;
typedef  TYPE_1__ br_block_cbcenc_class ;

/* Variables and functions */
 int /*<<< orphan*/  check_equals (char*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hextobin (unsigned char*,char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (void*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub2 (void*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  xor_buf (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static void
monte_carlo_DES_encrypt(const br_block_cbcenc_class *ve)
{
	unsigned char k1[8], k2[8], k3[8];
	unsigned char buf[8];
	unsigned char cipher[8];
	int i, j;
	br_des_gen_cbcenc_keys v_ec;
	void *ec;

	ec = &v_ec;
	hextobin(k1, "9ec2372c86379df4");
	hextobin(k2, "ad7ac4464f73805d");
	hextobin(k3, "20c4f87564527c91");
	hextobin(buf, "b624d6bd41783ab1");
	hextobin(cipher, "eafd97b190b167fe");
	for (i = 0; i < 400; i ++) {
		unsigned char key[24];

		memcpy(key, k1, 8);
		memcpy(key + 8, k2, 8);
		memcpy(key + 16, k3, 8);
		ve->init(ec, key, sizeof key);
		for (j = 0; j < 10000; j ++) {
			unsigned char iv[8];

			memset(iv, 0, sizeof iv);
			ve->run(ec, iv, buf, sizeof buf);
			switch (j) {
			case 9997: xor_buf(k3, buf, 8); break;
			case 9998: xor_buf(k2, buf, 8); break;
			case 9999: xor_buf(k1, buf, 8); break;
			}
		}
		printf(".");
		fflush(stdout);
	}
	printf(" ");
	fflush(stdout);
	check_equals("MC DES encrypt", buf, cipher, sizeof buf);
}
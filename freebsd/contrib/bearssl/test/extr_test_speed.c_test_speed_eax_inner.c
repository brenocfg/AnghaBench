#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  br_eax_context ;
struct TYPE_4__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *,unsigned char*,size_t) ;} ;
typedef  TYPE_1__ br_block_ctrcbc_class ;
struct TYPE_5__ {int /*<<< orphan*/  vtable; } ;
typedef  TYPE_2__ br_aes_gen_ctrcbc_keys ;

/* Variables and functions */
 double CLOCKS_PER_SEC ; 
 int /*<<< orphan*/  br_eax_aad_inject (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  br_eax_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_eax_get_tag (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  br_eax_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_eax_reset (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  br_eax_run (int /*<<< orphan*/ *,int,unsigned char*,int) ; 
 scalar_t__ clock () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

__attribute__((used)) static void
test_speed_eax_inner(char *name,
	const br_block_ctrcbc_class *vt, size_t key_len)
{
	unsigned char buf[8192], key[32], nonce[16], aad[16], tag[16];
	int i;
	long num;
	br_aes_gen_ctrcbc_keys ac;
	br_eax_context ec;

	if (vt == NULL) {
		printf("%-30s UNAVAILABLE\n", name);
		fflush(stdout);
		return;
	}
	memset(key, 'K', key_len);
	memset(nonce, 'N', sizeof nonce);
	memset(aad, 'A', sizeof aad);
	memset(buf, 'T', sizeof buf);
	for (i = 0; i < 10; i ++) {
		vt->init(&ac.vtable, key, key_len);
		br_eax_init(&ec, &ac.vtable);
		br_eax_reset(&ec, nonce, sizeof nonce);
		br_eax_aad_inject(&ec, aad, sizeof aad);
		br_eax_flip(&ec);
		br_eax_run(&ec, 1, buf, sizeof buf);
		br_eax_get_tag(&ec, tag);
	}
	num = 10;
	for (;;) {
		clock_t begin, end;
		double tt;
		long k;

		begin = clock();
		for (k = num; k > 0; k --) {
			vt->init(&ac.vtable, key, key_len);
			br_eax_init(&ec, &ac.vtable);
			br_eax_reset(&ec, nonce, sizeof nonce);
			br_eax_aad_inject(&ec, aad, sizeof aad);
			br_eax_flip(&ec);
			br_eax_run(&ec, 1, buf, sizeof buf);
			br_eax_get_tag(&ec, tag);
		}
		end = clock();
		tt = (double)(end - begin) / CLOCKS_PER_SEC;
		if (tt >= 2.0) {
			printf("%-30s %8.2f MB/s\n", name,
				((double)sizeof buf) * (double)num
				/ (tt * 1000000.0));
			fflush(stdout);
			return;
		}
		num <<= 1;
	}
}
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
typedef  int /*<<< orphan*/  br_block_ctr_class ;
typedef  int /*<<< orphan*/  br_block_cbcenc_class ;
typedef  int /*<<< orphan*/  br_block_cbcdec_class ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/ * br_aes_pwr8_cbcdec_get_vtable () ; 
 int /*<<< orphan*/ * br_aes_pwr8_cbcenc_get_vtable () ; 
 int /*<<< orphan*/ * br_aes_pwr8_ctr_get_vtable () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_AES_generic (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static void
test_AES_pwr8(void)
{
	const br_block_cbcenc_class *x_cbcenc;
	const br_block_cbcdec_class *x_cbcdec;
	const br_block_ctr_class *x_ctr;
	int hcbcenc, hcbcdec, hctr;

	x_cbcenc = br_aes_pwr8_cbcenc_get_vtable();
	x_cbcdec = br_aes_pwr8_cbcdec_get_vtable();
	x_ctr = br_aes_pwr8_ctr_get_vtable();
	hcbcenc = (x_cbcenc != NULL);
	hcbcdec = (x_cbcdec != NULL);
	hctr = (x_ctr != NULL);
	if (hcbcenc != hctr || hcbcdec != hctr) {
		fprintf(stderr, "AES_pwr8 availability mismatch (%d/%d/%d)\n",
			hcbcenc, hcbcdec, hctr);
		exit(EXIT_FAILURE);
	}
	if (hctr) {
		test_AES_generic("AES_pwr8",
			x_cbcenc, x_cbcdec, x_ctr, 1, 1);
	} else {
		printf("Test AES_pwr8: UNAVAILABLE\n");
	}
}
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
typedef  int /*<<< orphan*/  br_block_ctrcbc_class ;

/* Variables and functions */
 int /*<<< orphan*/ * br_aes_pwr8_ctrcbc_get_vtable () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_AES_CTRCBC_inner (char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
test_AES_CTRCBC_pwr8(void)
{
	const br_block_ctrcbc_class *vt;

	vt = br_aes_pwr8_ctrcbc_get_vtable();
	if (vt != NULL) {
		test_AES_CTRCBC_inner("pwr8", vt);
	} else {
		printf("Test AES CTR/CBC-MAC pwr8: UNAVAILABLE\n");
	}
}
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
 int /*<<< orphan*/  const br_aes_big_ctrcbc_vtable ; 
 int /*<<< orphan*/  const br_aes_ct64_ctrcbc_vtable ; 
 int /*<<< orphan*/  const br_aes_ct_ctrcbc_vtable ; 
 int /*<<< orphan*/ * br_aes_pwr8_ctrcbc_get_vtable () ; 
 int /*<<< orphan*/  const br_aes_small_ctrcbc_vtable ; 
 int /*<<< orphan*/ * br_aes_x86ni_ctrcbc_get_vtable () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_EAX_inner (char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
test_EAX(void)
{
	const br_block_ctrcbc_class *x_ctrcbc;

	test_EAX_inner("aes_big", &br_aes_big_ctrcbc_vtable);
	test_EAX_inner("aes_small", &br_aes_small_ctrcbc_vtable);
	test_EAX_inner("aes_ct", &br_aes_ct_ctrcbc_vtable);
	test_EAX_inner("aes_ct64", &br_aes_ct64_ctrcbc_vtable);

	x_ctrcbc = br_aes_x86ni_ctrcbc_get_vtable();
	if (x_ctrcbc != NULL) {
		test_EAX_inner("aes_x86ni", x_ctrcbc);
	} else {
		printf("Test EAX aes_x86ni: UNAVAILABLE\n");
	}

	x_ctrcbc = br_aes_pwr8_ctrcbc_get_vtable();
	if (x_ctrcbc != NULL) {
		test_EAX_inner("aes_pwr8", x_ctrcbc);
	} else {
		printf("Test EAX aes_pwr8: UNAVAILABLE\n");
	}
}
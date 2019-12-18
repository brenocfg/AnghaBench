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
 int /*<<< orphan*/  br_aes_ct64_ctrcbc_vtable ; 
 int /*<<< orphan*/  test_AES_CTRCBC_inner (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_AES_CTRCBC_ct64(void)
{
	test_AES_CTRCBC_inner("ct64", &br_aes_ct64_ctrcbc_vtable);
}
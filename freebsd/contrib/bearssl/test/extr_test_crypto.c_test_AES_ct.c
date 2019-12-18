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
 int /*<<< orphan*/  br_aes_ct_cbcdec_vtable ; 
 int /*<<< orphan*/  br_aes_ct_cbcenc_vtable ; 
 int /*<<< orphan*/  br_aes_ct_ctr_vtable ; 
 int /*<<< orphan*/  test_AES_generic (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
test_AES_ct(void)
{
	test_AES_generic("AES_ct",
		&br_aes_ct_cbcenc_vtable,
		&br_aes_ct_cbcdec_vtable,
		&br_aes_ct_ctr_vtable,
		1, 1);
}
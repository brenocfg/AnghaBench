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
typedef  int /*<<< orphan*/  br_aes_big_ctrcbc_keys ;

/* Variables and functions */
 int /*<<< orphan*/  br_aes_big_ctrcbc_ctr (int /*<<< orphan*/  const*,void*,void*,size_t) ; 
 int /*<<< orphan*/  br_aes_big_ctrcbc_mac (int /*<<< orphan*/  const*,void*,void*,size_t) ; 

void
br_aes_big_ctrcbc_decrypt(const br_aes_big_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len)
{
	br_aes_big_ctrcbc_mac(ctx, cbcmac, data, len);
	br_aes_big_ctrcbc_ctr(ctx, ctr, data, len);
}
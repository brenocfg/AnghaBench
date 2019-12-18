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
struct TYPE_3__ {int /*<<< orphan*/  skey; int /*<<< orphan*/  num_rounds; } ;
typedef  TYPE_1__ br_aes_small_ctrcbc_keys ;

/* Variables and functions */
 int /*<<< orphan*/  br_aes_small_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  xorbuf (void*,unsigned char const*,int) ; 

void
br_aes_small_ctrcbc_mac(const br_aes_small_ctrcbc_keys *ctx,
	void *cbcmac, const void *data, size_t len)
{
	const unsigned char *buf;

	buf = data;
	while (len > 0) {
		xorbuf(cbcmac, buf, 16);
		br_aes_small_encrypt(ctx->num_rounds, ctx->skey, cbcmac);
		buf += 16;
		len -= 16;
	}
}
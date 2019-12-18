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
struct TYPE_4__ {int /*<<< orphan*/  hmac_ctx; int /*<<< orphan*/  prk_ctx; } ;
struct TYPE_5__ {scalar_t__ chunk_num; int /*<<< orphan*/  dig_len; int /*<<< orphan*/  ptr; TYPE_1__ u; } ;
typedef  TYPE_2__ br_hkdf_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_hmac_get_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_hmac_key_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_hmac_out (int /*<<< orphan*/ *,unsigned char*) ; 

void
br_hkdf_flip(br_hkdf_context *hc)
{
	unsigned char tmp[64];

	br_hmac_out(&hc->u.hmac_ctx, tmp);
	br_hmac_key_init(&hc->u.prk_ctx,
		br_hmac_get_digest(&hc->u.hmac_ctx), tmp, hc->dig_len);
	hc->ptr = hc->dig_len;
	hc->chunk_num = 0;
}
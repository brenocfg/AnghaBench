#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {TYPE_3__* vtable; } ;
struct TYPE_7__ {int cc; TYPE_1__ sk; } ;
typedef  TYPE_2__ br_aesctr_drbg_context ;
struct TYPE_8__ {int (* run ) (TYPE_3__**,unsigned char*,int,unsigned char*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  br_aesctr_drbg_update (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int stub1 (TYPE_3__**,unsigned char*,int,unsigned char*,size_t) ; 

void
br_aesctr_drbg_generate(br_aesctr_drbg_context *ctx, void *out, size_t len)
{
	unsigned char *buf;
	unsigned char iv[12];

	buf = out;
	memset(iv, 0, sizeof iv);
	while (len > 0) {
		size_t clen;

		/*
		 * We generate data by blocks of at most 65280 bytes. This
		 * allows for unambiguously testing the counter overflow
		 * condition; also, it should work on 16-bit architectures
		 * (where 'size_t' is 16 bits only).
		 */
		clen = len;
		if (clen > 65280) {
			clen = 65280;
		}

		/*
		 * We make sure that the counter won't exceed the configured
		 * limit.
		 */
		if ((uint32_t)(ctx->cc + ((clen + 15) >> 4)) > 32768) {
			clen = (32768 - ctx->cc) << 4;
			if (clen > len) {
				clen = len;
			}
		}

		/*
		 * Run CTR.
		 */
		memset(buf, 0, clen);
		ctx->cc = ctx->sk.vtable->run(&ctx->sk.vtable,
			iv, ctx->cc, buf, clen);
		buf += clen;
		len -= clen;

		/*
		 * Every 32768 blocks, we force a state update.
		 */
		if (ctx->cc >= 32768) {
			br_aesctr_drbg_update(ctx, NULL, 0);
		}
	}
}
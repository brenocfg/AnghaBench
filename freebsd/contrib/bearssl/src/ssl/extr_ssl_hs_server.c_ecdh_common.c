#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  rng; } ;
struct TYPE_4__ {TYPE_3__ eng; } ;
typedef  TYPE_1__ br_ssl_server_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_ccopy (int,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_hmac_drbg_generate (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_ssl_engine_compute_master (TYPE_3__*,int,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
ecdh_common(br_ssl_server_context *ctx, int prf_id,
	unsigned char *xcoor, size_t xcoor_len, uint32_t ctl)
{
	unsigned char rpms[80];

	if (xcoor_len > sizeof rpms) {
		xcoor_len = sizeof rpms;
		ctl = 0;
	}

	/*
	 * Make a random PMS and copy it above the decrypted value if the
	 * decryption failed. Note that we use a constant-time conditional
	 * copy.
	 */
	br_hmac_drbg_generate(&ctx->eng.rng, rpms, xcoor_len);
	br_ccopy(ctl ^ 1, xcoor, rpms, xcoor_len);

	/*
	 * Compute master secret.
	 */
	br_ssl_engine_compute_master(&ctx->eng, prf_id, xcoor, xcoor_len);

	/*
	 * Clear the pre-master secret from RAM: it is normally a buffer
	 * in the context, hence potentially long-lived.
	 */
	memset(xcoor, 0, xcoor_len);
}
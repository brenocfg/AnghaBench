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
typedef  int /*<<< orphan*/  const UCHAR ;
typedef  int /*<<< orphan*/  MY_SHA0_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MY_SHA0_DIGEST_SIZE ; 
 int /*<<< orphan*/  MY_SHA0_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MY_SHA0_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MY_SHA0_update (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const UCHAR* MY_SHA0_hash(const void* data, int len, UCHAR* digest) {
	MY_SHA0_CTX ctx;
	MY_SHA0_init(&ctx);
	MY_SHA0_update(&ctx, data, len);
	memcpy(digest, MY_SHA0_final(&ctx), MY_SHA0_DIGEST_SIZE);
	return digest;
}
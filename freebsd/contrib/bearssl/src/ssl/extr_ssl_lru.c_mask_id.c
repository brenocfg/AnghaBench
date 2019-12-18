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
struct TYPE_3__ {int /*<<< orphan*/  index_key; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ br_ssl_session_cache_lru ;
typedef  int /*<<< orphan*/  br_hmac_key_context ;
typedef  int /*<<< orphan*/  br_hmac_context ;

/* Variables and functions */
 int /*<<< orphan*/  SESSION_ID_LEN ; 
 int /*<<< orphan*/  br_hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_hmac_key_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  br_hmac_out (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  br_hmac_update (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mask_id(br_ssl_session_cache_lru *cc,
	const unsigned char *src, unsigned char *dst)
{
	br_hmac_key_context hkc;
	br_hmac_context hc;

	memcpy(dst, src, SESSION_ID_LEN);
	br_hmac_key_init(&hkc, cc->hash, cc->index_key, sizeof cc->index_key);
	br_hmac_init(&hc, &hkc, SESSION_ID_LEN);
	br_hmac_update(&hc, src, SESSION_ID_LEN);
	br_hmac_out(&hc, dst);
}
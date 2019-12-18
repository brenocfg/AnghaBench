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
typedef  int /*<<< orphan*/  esp_sha_type ;
typedef  int /*<<< orphan*/  SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  esp_sha_lock_engine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_sha_unlock_engine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ets_sha_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  ets_sha_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ets_sha_starts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ets_sha_update (int /*<<< orphan*/ *,unsigned char const*,size_t,int) ; 

void esp_sha(esp_sha_type sha_type, const unsigned char *input, size_t ilen, unsigned char *output)
{
    SHA_CTX ctx;

    esp_sha_lock_engine(sha_type);

    ets_sha_init(&ctx, sha_type);
    ets_sha_starts(&ctx, 0);
    ets_sha_update(&ctx, input, ilen, false);
    ets_sha_finish(&ctx, output);

    esp_sha_unlock_engine(sha_type);
}
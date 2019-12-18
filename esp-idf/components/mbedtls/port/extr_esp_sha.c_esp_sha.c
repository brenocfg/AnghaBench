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
typedef  int /*<<< orphan*/  mbedtls_sha512_context ;
typedef  int /*<<< orphan*/  mbedtls_sha256_context ;
typedef  int /*<<< orphan*/  mbedtls_sha1_context ;
typedef  scalar_t__ esp_sha_type ;

/* Variables and functions */
 scalar_t__ SHA1 ; 
 scalar_t__ SHA2_256 ; 
 scalar_t__ SHA2_384 ; 
 scalar_t__ SHA2_512 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int mbedtls_sha1_finish_ret (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha1_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_starts_ret (int /*<<< orphan*/ *) ; 
 int mbedtls_sha1_update_ret (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int mbedtls_sha256_finish_ret (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha256_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_starts_ret (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mbedtls_sha256_update_ret (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int mbedtls_sha512_finish_ret (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha512_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha512_starts_ret (int /*<<< orphan*/ *,int) ; 
 int mbedtls_sha512_update_ret (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

void esp_sha(esp_sha_type sha_type, const unsigned char *input, size_t ilen, unsigned char *output)
{
    int ret;
    assert(input != NULL && output != NULL);

    if (sha_type == SHA1) {

        mbedtls_sha1_context *ctx1 = (mbedtls_sha1_context *)malloc(sizeof(mbedtls_sha1_context));
        assert(ctx1 != NULL);
        mbedtls_sha1_starts_ret(ctx1);
        ret = mbedtls_sha1_update_ret(ctx1, input, ilen);
        assert(ret == 0);
        ret = mbedtls_sha1_finish_ret(ctx1, output);
        assert(ret == 0);
        mbedtls_sha1_free(ctx1);
        free(ctx1);

    } else if (sha_type == SHA2_256) {

        mbedtls_sha256_context *ctx256 = (mbedtls_sha256_context *)malloc(sizeof(mbedtls_sha256_context));
        assert(ctx256 != NULL);
        mbedtls_sha256_starts_ret(ctx256, 0);
        ret = mbedtls_sha256_update_ret(ctx256, input, ilen);
        assert(ret == 0);
        ret = mbedtls_sha256_finish_ret(ctx256, output);
        assert(ret == 0);
        mbedtls_sha256_free(ctx256);
        free(ctx256);

    } else if (sha_type == SHA2_384) {

        mbedtls_sha512_context *ctx384 = (mbedtls_sha512_context *)malloc(sizeof(mbedtls_sha512_context));
        assert(ctx384 != NULL);
        mbedtls_sha512_starts_ret(ctx384, 1);
        ret = mbedtls_sha512_update_ret(ctx384, input, ilen);
        assert(ret == 0);
        ret = mbedtls_sha512_finish_ret(ctx384, output);
        assert(ret == 0);
        mbedtls_sha512_free(ctx384);
        free(ctx384);

    } else if (sha_type == SHA2_512) {

        mbedtls_sha512_context *ctx512 = (mbedtls_sha512_context *)malloc(sizeof(mbedtls_sha512_context));
        assert(ctx512 != NULL);
        mbedtls_sha512_starts_ret(ctx512, 0);
        ret = mbedtls_sha512_update_ret(ctx512, input, ilen);
        assert(ret == 0);
        ret = mbedtls_sha512_finish_ret(ctx512, output);
        assert(ret == 0);
        mbedtls_sha512_free(ctx512);
        free(ctx512);

    }

}
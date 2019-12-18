#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  pk; } ;
typedef  TYPE_1__ mbedtls_x509_crt ;
typedef  int /*<<< orphan*/  mbedtls_rsa_context ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX16_MESSAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX8_ARRAY (int /*<<< orphan*/  const*,char*,size_t) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (char*,size_t) ; 
 int /*<<< orphan*/ * mbedtls_pk_rsa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_rsa_check_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_rsa_public (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_info (char*,int,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_parse (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  pki_input ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void test_cert(const char *cert, const uint8_t *expected_output, size_t output_len)
{
    mbedtls_x509_crt crt;
    mbedtls_rsa_context *rsa;
    char buf[output_len];

    bzero(buf, output_len);

    mbedtls_x509_crt_init(&crt);

    TEST_ASSERT_EQUAL_HEX16_MESSAGE(0,
                                    -mbedtls_x509_crt_parse(&crt,
                                                            (const uint8_t *)cert,
                                                            strlen(cert)+1),
                                    "parse cert");

    rsa = mbedtls_pk_rsa(crt.pk);
    TEST_ASSERT_NOT_NULL(rsa);

    TEST_ASSERT_EQUAL_HEX16_MESSAGE(0,
                                    -mbedtls_rsa_check_pubkey(rsa),
                                    "check cert pubkey");

    mbedtls_x509_crt_info(buf, sizeof(buf), "", &crt);
    puts(buf);

    TEST_ASSERT_EQUAL_HEX16_MESSAGE(0,
                                    -mbedtls_rsa_public(rsa, pki_input, (uint8_t *)buf),
                                    "RSA PK operation");

    /*
    // Dump buffer for debugging
    for(int i = 0; i < output_len; i++) {
        printf("0x%02x, ", buf[i]);
    }
    printf("\n");
    */

    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_output, buf, output_len);

    mbedtls_x509_crt_free(&crt);
}
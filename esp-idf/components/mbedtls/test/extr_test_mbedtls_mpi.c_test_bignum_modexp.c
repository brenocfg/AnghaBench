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
typedef  int /*<<< orphan*/  z_buf ;
typedef  int /*<<< orphan*/  mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_OK ; 
 int /*<<< orphan*/  TEST_ASSERT_FALSE (int /*<<< orphan*/ ) ; 
 int mbedtls_mpi_exp_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_read_string (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_write_string (int /*<<< orphan*/ *,int,char*,int,size_t*) ; 
 scalar_t__ memcmp (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static bool test_bignum_modexp(const char *z_str, const char *x_str, const char *y_str, const char *m_str, int ret_error)
{
    mbedtls_mpi Z, X, Y, M;
    char z_buf[400] = { 0 };
    size_t z_buf_len = 0;
    bool fail = false;

    printf("%s = (%s ^ %s) mod %s  ret=%d ... ", z_str, x_str, y_str, m_str, ret_error);

    mbedtls_mpi_init(&Z);
    mbedtls_mpi_init(&X);
    mbedtls_mpi_init(&Y);
    mbedtls_mpi_init(&M);

    TEST_ASSERT_FALSE(mbedtls_mpi_read_string(&X, 16, x_str));
    TEST_ASSERT_FALSE(mbedtls_mpi_read_string(&Y, 16, y_str));
    TEST_ASSERT_FALSE(mbedtls_mpi_read_string(&M, 16, m_str));

    //mbedtls_mpi_printf("X", &X);
    //mbedtls_mpi_printf("X", &Y);
    //mbedtls_mpi_printf("M", &M);

    /* Z = (X ^ Y) mod M */
    if (ret_error != mbedtls_mpi_exp_mod(&Z, &X, &Y, &M, NULL)) {
        fail = true;
    }

    if (ret_error == MBEDTLS_OK) {
        mbedtls_mpi_write_string(&Z, 16, z_buf, sizeof(z_buf)-1, &z_buf_len);
        if (memcmp(z_str, z_buf, strlen(z_str)) != 0) {
            printf("\n Expected '%s' Was '%s' \n", z_str, z_buf);
            fail = true;
        }
    }

    mbedtls_mpi_free(&Z);
    mbedtls_mpi_free(&X);
    mbedtls_mpi_free(&Y);
    mbedtls_mpi_free(&M);

    if (fail == true) {
        printf(" FAIL\n");
    } else {
        printf(" PASS\n");
    }
    return fail;
}
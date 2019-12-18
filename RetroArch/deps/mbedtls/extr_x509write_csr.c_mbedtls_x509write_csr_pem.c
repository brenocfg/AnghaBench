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
typedef  int /*<<< orphan*/  output_buf ;
typedef  int /*<<< orphan*/  mbedtls_x509write_csr ;

/* Variables and functions */
 int /*<<< orphan*/  PEM_BEGIN_CSR ; 
 int /*<<< orphan*/  PEM_END_CSR ; 
 int mbedtls_pem_write_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,size_t,size_t*) ; 
 int mbedtls_x509write_csr_der (int /*<<< orphan*/ *,unsigned char*,int,int (*) (void*,unsigned char*,size_t),void*) ; 

int mbedtls_x509write_csr_pem( mbedtls_x509write_csr *ctx, unsigned char *buf, size_t size,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng )
{
    int ret;
    unsigned char output_buf[4096];
    size_t olen = 0;

    if( ( ret = mbedtls_x509write_csr_der( ctx, output_buf, sizeof(output_buf),
                                   f_rng, p_rng ) ) < 0 )
    {
        return( ret );
    }

    if( ( ret = mbedtls_pem_write_buffer( PEM_BEGIN_CSR, PEM_END_CSR,
                                  output_buf + sizeof(output_buf) - ret,
                                  ret, buf, size, &olen ) ) != 0 )
    {
        return( ret );
    }

    return( 0 );
}
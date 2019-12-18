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
typedef  int /*<<< orphan*/  mbedtls_ecp_keypair ;

/* Variables and functions */
 int mbedtls_ecp_check_pub_priv (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int eckey_check_pair( const void *pub, const void *prv )
{
    return( mbedtls_ecp_check_pub_priv( (const mbedtls_ecp_keypair *) pub,
                                (const mbedtls_ecp_keypair *) prv ) );
}
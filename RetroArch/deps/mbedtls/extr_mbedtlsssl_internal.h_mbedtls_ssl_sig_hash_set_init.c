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
typedef  int /*<<< orphan*/  mbedtls_ssl_sig_hash_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MD_NONE ; 
 int /*<<< orphan*/  mbedtls_ssl_sig_hash_set_const_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mbedtls_ssl_sig_hash_set_init( mbedtls_ssl_sig_hash_set_t *set )
{
    mbedtls_ssl_sig_hash_set_const_hash( set, MBEDTLS_MD_NONE );
}
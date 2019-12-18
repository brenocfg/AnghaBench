#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rsa_min_bitlen; int allowed_curves; } ;
typedef  TYPE_2__ mbedtls_x509_crt_profile ;
typedef  scalar_t__ mbedtls_pk_type_t ;
typedef  int /*<<< orphan*/  mbedtls_pk_context ;
typedef  int /*<<< orphan*/  mbedtls_ecp_group_id ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_1__ grp; } ;

/* Variables and functions */
 scalar_t__ MBEDTLS_PK_ECDSA ; 
 scalar_t__ MBEDTLS_PK_ECKEY ; 
 scalar_t__ MBEDTLS_PK_ECKEY_DH ; 
 scalar_t__ MBEDTLS_PK_RSA ; 
 scalar_t__ MBEDTLS_PK_RSASSA_PSS ; 
 int MBEDTLS_X509_ID_FLAG (int /*<<< orphan*/ ) ; 
 TYPE_4__* mbedtls_pk_ec (int /*<<< orphan*/  const) ; 
 scalar_t__ mbedtls_pk_get_bitlen (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int x509_profile_check_key( const mbedtls_x509_crt_profile *profile,
                                   mbedtls_pk_type_t pk_alg,
                                   const mbedtls_pk_context *pk )
{
#if defined(MBEDTLS_RSA_C)
    if( pk_alg == MBEDTLS_PK_RSA || pk_alg == MBEDTLS_PK_RSASSA_PSS )
    {
        if( mbedtls_pk_get_bitlen( pk ) >= profile->rsa_min_bitlen )
            return( 0 );

        return( -1 );
    }
#endif

#if defined(MBEDTLS_ECP_C)
    if( pk_alg == MBEDTLS_PK_ECDSA ||
        pk_alg == MBEDTLS_PK_ECKEY ||
        pk_alg == MBEDTLS_PK_ECKEY_DH )
    {
        mbedtls_ecp_group_id gid = mbedtls_pk_ec( *pk )->grp.id;

        if( ( profile->allowed_curves & MBEDTLS_X509_ID_FLAG( gid ) ) != 0 )
            return( 0 );

        return( -1 );
    }
#endif

    return( -1 );
}
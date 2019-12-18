#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  p; } ;
struct TYPE_7__ {int version; int /*<<< orphan*/  ca_istrue; TYPE_1__ raw; int /*<<< orphan*/  subject; int /*<<< orphan*/  issuer; } ;
typedef  TYPE_2__ mbedtls_x509_crt ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_X509_KU_KEY_CERT_SIGN ; 
 scalar_t__ mbedtls_x509_crt_check_key_usage (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ x509_name_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int x509_crt_check_parent( const mbedtls_x509_crt *child,
                                  const mbedtls_x509_crt *parent,
                                  int top, int bottom )
{
    int need_ca_bit;

    /* Parent must be the issuer */
    if( x509_name_cmp( &child->issuer, &parent->subject ) != 0 )
        return( -1 );

    /* Parent must have the basicConstraints CA bit set as a general rule */
    need_ca_bit = 1;

    /* Exception: v1/v2 certificates that are locally trusted. */
    if( top && parent->version < 3 )
        need_ca_bit = 0;

    /* Exception: self-signed end-entity certs that are locally trusted. */
    if( top && bottom &&
        child->raw.len == parent->raw.len &&
        memcmp( child->raw.p, parent->raw.p, child->raw.len ) == 0 )
    {
        need_ca_bit = 0;
    }

    if( need_ca_bit && ! parent->ca_istrue )
        return( -1 );

#if defined(MBEDTLS_X509_CHECK_KEY_USAGE)
    if( need_ca_bit &&
        mbedtls_x509_crt_check_key_usage( parent, MBEDTLS_X509_KU_KEY_CERT_SIGN ) != 0 )
    {
        return( -1 );
    }
#endif

    return( 0 );
}
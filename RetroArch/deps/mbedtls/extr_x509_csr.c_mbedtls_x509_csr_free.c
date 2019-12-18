#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int len; TYPE_3__* p; } ;
struct TYPE_9__ {TYPE_3__* next; } ;
struct TYPE_10__ {TYPE_1__ raw; struct TYPE_10__* next; TYPE_2__ subject; struct TYPE_10__* sig_opts; int /*<<< orphan*/  pk; } ;
typedef  TYPE_3__ mbedtls_x509_name ;
typedef  TYPE_3__ mbedtls_x509_csr ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_free (TYPE_3__*) ; 
 int /*<<< orphan*/  mbedtls_pk_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_3__*,int) ; 

void mbedtls_x509_csr_free( mbedtls_x509_csr *csr )
{
    mbedtls_x509_name *name_cur;
    mbedtls_x509_name *name_prv;

    if( csr == NULL )
        return;

    mbedtls_pk_free( &csr->pk );

#if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT)
    mbedtls_free( csr->sig_opts );
#endif

    name_cur = csr->subject.next;
    while( name_cur != NULL )
    {
        name_prv = name_cur;
        name_cur = name_cur->next;
        mbedtls_zeroize( name_prv, sizeof( mbedtls_x509_name ) );
        mbedtls_free( name_prv );
    }

    if( csr->raw.p != NULL )
    {
        mbedtls_zeroize( csr->raw.p, csr->raw.len );
        mbedtls_free( csr->raw.p );
    }

    mbedtls_zeroize( csr, sizeof( mbedtls_x509_csr ) );
}
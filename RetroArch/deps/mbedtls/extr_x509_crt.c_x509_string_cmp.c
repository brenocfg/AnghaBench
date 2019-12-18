#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tag; scalar_t__ len; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ mbedtls_x509_buf ;

/* Variables and functions */
 scalar_t__ MBEDTLS_ASN1_PRINTABLE_STRING ; 
 scalar_t__ MBEDTLS_ASN1_UTF8_STRING ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ x509_memcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int x509_string_cmp( const mbedtls_x509_buf *a, const mbedtls_x509_buf *b )
{
    if( a->tag == b->tag &&
        a->len == b->len &&
        memcmp( a->p, b->p, b->len ) == 0 )
    {
        return( 0 );
    }

    if( ( a->tag == MBEDTLS_ASN1_UTF8_STRING || a->tag == MBEDTLS_ASN1_PRINTABLE_STRING ) &&
        ( b->tag == MBEDTLS_ASN1_UTF8_STRING || b->tag == MBEDTLS_ASN1_PRINTABLE_STRING ) &&
        a->len == b->len &&
        x509_memcasecmp( a->p, b->p, b->len ) == 0 )
    {
        return( 0 );
    }

    return( -1 );
}
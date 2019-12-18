#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p; } ;
struct TYPE_6__ {int /*<<< orphan*/  p; } ;
struct TYPE_8__ {TYPE_2__ val; TYPE_1__ oid; } ;
typedef  TYPE_3__ mbedtls_asn1_named_data ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_3__*,int) ; 

void mbedtls_asn1_free_named_data( mbedtls_asn1_named_data *cur )
{
    if( cur == NULL )
        return;

    mbedtls_free( cur->oid.p );
    mbedtls_free( cur->val.p );

    mbedtls_zeroize( cur, sizeof( mbedtls_asn1_named_data ) );
}
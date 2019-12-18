#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Q; int /*<<< orphan*/  d; int /*<<< orphan*/  grp; } ;
typedef  TYPE_1__ mbedtls_ecp_keypair ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_ecp_group_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 

void mbedtls_ecp_keypair_free( mbedtls_ecp_keypair *key )
{
    if( key == NULL )
        return;

    mbedtls_ecp_group_free( &key->grp );
    mbedtls_mpi_free( &key->d );
    mbedtls_ecp_point_free( &key->Q );
}
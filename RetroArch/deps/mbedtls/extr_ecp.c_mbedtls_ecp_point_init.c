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
struct TYPE_3__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 

void mbedtls_ecp_point_init( mbedtls_ecp_point *pt )
{
    if( pt == NULL )
        return;

    mbedtls_mpi_init( &pt->X );
    mbedtls_mpi_init( &pt->Y );
    mbedtls_mpi_init( &pt->Z );
}
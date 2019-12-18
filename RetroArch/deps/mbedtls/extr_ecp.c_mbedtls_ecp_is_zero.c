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
struct TYPE_3__ {int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;

/* Variables and functions */
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mbedtls_ecp_is_zero( mbedtls_ecp_point *pt )
{
    return( mbedtls_mpi_cmp_int( &pt->Z, 0 ) == 0 );
}
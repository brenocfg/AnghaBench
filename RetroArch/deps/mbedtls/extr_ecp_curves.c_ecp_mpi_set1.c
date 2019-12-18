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
typedef  int mbedtls_mpi_uint ;
struct TYPE_3__ {int s; int n; int* p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */

__attribute__((used)) static void ecp_mpi_set1( mbedtls_mpi *X )
{
    static mbedtls_mpi_uint one[] = { 1 };
    X->s = 1;
    X->n = 1;
    X->p = one;
}
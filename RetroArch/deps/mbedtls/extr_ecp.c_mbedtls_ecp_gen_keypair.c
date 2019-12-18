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
typedef  int /*<<< orphan*/  mbedtls_mpi ;
typedef  int /*<<< orphan*/  mbedtls_ecp_point ;
struct TYPE_4__ {int /*<<< orphan*/  G; } ;
typedef  TYPE_1__ mbedtls_ecp_group ;

/* Variables and functions */
 int mbedtls_ecp_gen_keypair_base (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int (*) (void*,unsigned char*,size_t),void*) ; 

int mbedtls_ecp_gen_keypair( mbedtls_ecp_group *grp,
                             mbedtls_mpi *d, mbedtls_ecp_point *Q,
                             int (*f_rng)(void *, unsigned char *, size_t),
                             void *p_rng )
{
    return( mbedtls_ecp_gen_keypair_base( grp, &grp->G, d, Q, f_rng, p_rng ) );
}
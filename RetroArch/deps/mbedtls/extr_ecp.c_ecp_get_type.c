#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
struct TYPE_6__ {int /*<<< orphan*/ * p; } ;
struct TYPE_8__ {TYPE_2__ Y; TYPE_1__ X; } ;
struct TYPE_9__ {TYPE_3__ G; } ;
typedef  TYPE_4__ mbedtls_ecp_group ;
typedef  int /*<<< orphan*/  ecp_curve_type ;

/* Variables and functions */
 int /*<<< orphan*/  ECP_TYPE_MONTGOMERY ; 
 int /*<<< orphan*/  ECP_TYPE_NONE ; 
 int /*<<< orphan*/  ECP_TYPE_SHORT_WEIERSTRASS ; 

__attribute__((used)) static ecp_curve_type ecp_get_type( const mbedtls_ecp_group *grp )
{
    if( grp->G.X.p == NULL )
        return( ECP_TYPE_NONE );

    if( grp->G.Y.p == NULL )
        return( ECP_TYPE_MONTGOMERY );
    return( ECP_TYPE_SHORT_WEIERSTRASS );
}
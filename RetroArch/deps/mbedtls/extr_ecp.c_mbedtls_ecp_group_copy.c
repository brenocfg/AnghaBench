#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ mbedtls_ecp_group ;

/* Variables and functions */
 int mbedtls_ecp_group_load (TYPE_1__*,int /*<<< orphan*/ ) ; 

int mbedtls_ecp_group_copy( mbedtls_ecp_group *dst, const mbedtls_ecp_group *src )
{
    return mbedtls_ecp_group_load( dst, src->id );
}
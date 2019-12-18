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
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ mbedtls_md_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MD_NONE ; 

mbedtls_md_type_t mbedtls_md_get_type( const mbedtls_md_info_t *md_info )
{
    if( md_info == NULL )
        return( MBEDTLS_MD_NONE );

    return md_info->type;
}
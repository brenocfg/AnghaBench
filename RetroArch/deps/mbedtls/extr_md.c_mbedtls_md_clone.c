#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  md_ctx; TYPE_1__* md_info; } ;
typedef  TYPE_2__ mbedtls_md_context_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* clone_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MBEDTLS_ERR_MD_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mbedtls_md_clone( mbedtls_md_context_t *dst,
                      const mbedtls_md_context_t *src )
{
    if( dst == NULL || dst->md_info == NULL ||
        src == NULL || src->md_info == NULL ||
        dst->md_info != src->md_info )
    {
        return( MBEDTLS_ERR_MD_BAD_INPUT_DATA );
    }

    dst->md_info->clone_func( dst->md_ctx, src->md_ctx );

    return( 0 );
}
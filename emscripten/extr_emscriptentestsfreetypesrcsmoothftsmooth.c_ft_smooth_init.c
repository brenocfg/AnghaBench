#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  raster_pool_size; int /*<<< orphan*/  raster_pool; } ;
struct TYPE_10__ {int /*<<< orphan*/  raster; TYPE_2__* clazz; } ;
struct TYPE_9__ {TYPE_1__* raster_class; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* raster_reset ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__* FT_Renderer ;
typedef  TYPE_4__* FT_Library ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 TYPE_4__* FT_MODULE_LIBRARY (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  ft_smooth_init( FT_Renderer  render )
  {
    FT_Library  library = FT_MODULE_LIBRARY( render );


    render->clazz->raster_class->raster_reset( render->raster,
                                               library->raster_pool,
                                               library->raster_pool_size );

    return 0;
  }
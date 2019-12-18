#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * renderchain_data; TYPE_1__* renderchain_driver; } ;
typedef  TYPE_2__ d3d9_video_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* chain_free ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d3d9_deinit_chain(d3d9_video_t *d3d)
{
   if (!d3d || !d3d->renderchain_driver)
      return;

   if (d3d->renderchain_driver->chain_free)
      d3d->renderchain_driver->chain_free(d3d->renderchain_data);

   d3d->renderchain_driver = NULL;
   d3d->renderchain_data   = NULL;
}
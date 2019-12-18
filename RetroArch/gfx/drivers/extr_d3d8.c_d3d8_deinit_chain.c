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
struct TYPE_3__ {int /*<<< orphan*/ * renderchain_data; } ;
typedef  TYPE_1__ d3d8_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d8_renderchain_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d3d8_deinit_chain(d3d8_video_t *d3d)
{
   d3d8_renderchain_free(d3d->renderchain_data);

   d3d->renderchain_data   = NULL;
}
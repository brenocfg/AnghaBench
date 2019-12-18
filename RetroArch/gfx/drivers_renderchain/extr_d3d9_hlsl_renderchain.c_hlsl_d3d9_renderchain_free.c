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
struct TYPE_4__ {int /*<<< orphan*/  chain; } ;
typedef  TYPE_1__ hlsl_renderchain_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_hlsl_destroy_resources (TYPE_1__*) ; 
 int /*<<< orphan*/  d3d9_renderchain_destroy_passes_and_luts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void hlsl_d3d9_renderchain_free(void *data)
{
   hlsl_renderchain_t *chain = (hlsl_renderchain_t*)data;

   if (!chain)
      return;

   d3d9_hlsl_destroy_resources(chain);
   d3d9_renderchain_destroy_passes_and_luts(&chain->chain);
   free(chain);
}
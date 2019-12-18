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
struct TYPE_3__ {int /*<<< orphan*/  vertex_decl; int /*<<< orphan*/  vertex_buf; scalar_t__ tex; } ;
typedef  TYPE_1__ d3d8_renderchain_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d8_texture_free (scalar_t__) ; 
 int /*<<< orphan*/  d3d8_vertex_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void d3d8_renderchain_free(void *data)
{
   d3d8_renderchain_t *chain = (d3d8_renderchain_t*)data;

   if (!chain)
      return;

   if (chain->tex)
      d3d8_texture_free(chain->tex);
   d3d8_vertex_buffer_free(chain->vertex_buf, chain->vertex_decl);

   free(chain);
}
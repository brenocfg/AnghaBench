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
struct TYPE_8__ {TYPE_2__* passes; } ;
struct TYPE_9__ {TYPE_3__ chain; } ;
typedef  TYPE_4__ hlsl_renderchain_t ;
struct TYPE_7__ {int count; TYPE_1__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  vertex_decl; int /*<<< orphan*/ * vertex_buf; int /*<<< orphan*/ * tex; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  d3d9_texture_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d9_vertex_buffer_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d3d9_hlsl_deinit_progs(hlsl_renderchain_t *chain)
{
   RARCH_LOG("[D3D9 HLSL]: Destroying programs.\n");

   if (chain->chain.passes->count >= 1)
   {
      unsigned i;

      d3d9_vertex_buffer_free(NULL, chain->chain.passes->data[0].vertex_decl);

      for (i = 1; i < chain->chain.passes->count; i++)
      {
         if (chain->chain.passes->data[i].tex)
            d3d9_texture_free(chain->chain.passes->data[i].tex);
         chain->chain.passes->data[i].tex = NULL;
         d3d9_vertex_buffer_free(
               chain->chain.passes->data[i].vertex_buf,
               chain->chain.passes->data[i].vertex_decl);
      }
   }
}
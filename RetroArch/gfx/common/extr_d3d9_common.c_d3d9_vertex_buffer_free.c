#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * LPDIRECT3DVERTEXDECLARATION9 ;
typedef  int /*<<< orphan*/ * LPDIRECT3DVERTEXBUFFER9 ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DVertexBuffer9_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d9_vertex_declaration_free (int /*<<< orphan*/ *) ; 

void d3d9_vertex_buffer_free(void *vertex_data, void *vertex_declaration)
{
   if (vertex_data)
   {
      LPDIRECT3DVERTEXBUFFER9 buf =
         (LPDIRECT3DVERTEXBUFFER9)vertex_data;
      IDirect3DVertexBuffer9_Release(buf);
      buf = NULL;
   }

   if (vertex_declaration)
   {
      LPDIRECT3DVERTEXDECLARATION9 vertex_decl =
         (LPDIRECT3DVERTEXDECLARATION9)vertex_declaration;
      d3d9_vertex_declaration_free(vertex_decl);
      vertex_decl = NULL;
   }
}
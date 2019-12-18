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
typedef  int /*<<< orphan*/  LPDIRECT3DVERTEXBUFFER9 ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9 ;
typedef  scalar_t__ INT32 ;
typedef  int /*<<< orphan*/  D3DPOOL ;

/* Variables and functions */
 unsigned int D3DUSAGE_SOFTWAREPROCESSING ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_CreateVertexBuffer (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirect3DDevice9_GetSoftwareVertexProcessing (int /*<<< orphan*/ ) ; 

void *d3d9_vertex_buffer_new(void *_dev,
      unsigned length, unsigned usage,
      unsigned fvf, INT32 pool, void *handle)
{
   void              *buf = NULL;
   LPDIRECT3DDEVICE9 dev  = (LPDIRECT3DDEVICE9)_dev;

#ifndef _XBOX
   if (usage == 0)
      if (IDirect3DDevice9_GetSoftwareVertexProcessing(dev))
         usage = D3DUSAGE_SOFTWAREPROCESSING;
#endif

   if (FAILED(IDirect3DDevice9_CreateVertexBuffer(
               dev, length, usage, fvf,
               (D3DPOOL)pool,
               (LPDIRECT3DVERTEXBUFFER9*)&buf, NULL)))
      return NULL;

   return buf;
}
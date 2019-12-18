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
typedef  scalar_t__ LPDIRECT3DTEXTURE9 ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_texture_free (scalar_t__) ; 

__attribute__((used)) static void d3d9_unload_texture(void *data, uintptr_t id)
{
   LPDIRECT3DTEXTURE9 texid;
   if (!id)
      return;

   texid = (LPDIRECT3DTEXTURE9)id;
   d3d9_texture_free(texid);
}
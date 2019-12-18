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
typedef  int u32 ;
struct ctr_texture {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ctr_texture*) ; 
 int /*<<< orphan*/  linearFree (scalar_t__) ; 
 int /*<<< orphan*/  vramFree (scalar_t__) ; 

__attribute__((used)) static void ctr_unload_texture(void *data, uintptr_t handle)
{
   struct ctr_texture *texture   = (struct ctr_texture*)handle;

   if (!texture)
      return;

   if (texture->data)
   {
      if(((u32)texture->data & 0xFF000000) == 0x1F000000)
         vramFree(texture->data);
      else
         linearFree(texture->data);
   }
   free(texture);
}
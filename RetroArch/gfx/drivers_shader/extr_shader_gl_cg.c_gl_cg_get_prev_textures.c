#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* prg; TYPE_2__* shader; } ;
typedef  TYPE_4__ cg_shader_data_t ;
struct TYPE_7__ {scalar_t__ tex; } ;
struct TYPE_6__ {unsigned int passes; } ;
struct TYPE_5__ {TYPE_3__* prev; } ;

/* Variables and functions */
 unsigned int MAX (unsigned int,unsigned int) ; 
 unsigned int PREV_TEXTURES ; 

__attribute__((used)) static unsigned gl_cg_get_prev_textures(void *data)
{
   unsigned i, j;
   unsigned max_prev = 0;
   cg_shader_data_t *cg = (cg_shader_data_t*)data;

   if (!cg)
      return 0;

   for (i = 1; i <= cg->shader->passes; i++)
      for (j = 0; j < PREV_TEXTURES; j++)
         if (cg->prg[i].prev[j].tex)
            max_prev = MAX(j + 1, max_prev);

   return max_prev;
}
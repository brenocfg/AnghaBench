#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int idx; int /*<<< orphan*/  len; scalar_t__* s; } ;
typedef  TYPE_3__ rcheevos_ctx_desc_t ;
struct TYPE_10__ {TYPE_1__* info; } ;
typedef  TYPE_4__ rcheevos_cheevo_t ;
struct TYPE_8__ {unsigned int core_count; unsigned int unofficial_count; } ;
struct TYPE_11__ {TYPE_4__* unofficial; TYPE_2__ patchdata; TYPE_4__* core; } ;
struct TYPE_7__ {int /*<<< orphan*/  description; } ;

/* Variables and functions */
 scalar_t__ rcheevos_loaded ; 
 TYPE_5__ rcheevos_locals ; 
 int /*<<< orphan*/  strlcpy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool rcheevos_get_description(rcheevos_ctx_desc_t* desc)
{
   unsigned idx;
   const rcheevos_cheevo_t* cheevo;

   if (!desc)
      return false;

   *desc->s = 0;

   if (rcheevos_loaded)
   {
      idx = desc->idx;

      if (idx < rcheevos_locals.patchdata.core_count)
         cheevo = rcheevos_locals.core + idx;
      else
      {
         idx -= rcheevos_locals.patchdata.core_count;

         if (idx < rcheevos_locals.patchdata.unofficial_count)
            cheevo = rcheevos_locals.unofficial + idx;
         else
            return true;
      }

      strlcpy(desc->s, cheevo->info->description, desc->len);
   }

   return true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  string; } ;
struct TYPE_10__ {int /*<<< orphan*/  string; } ;
struct TYPE_8__ {int /*<<< orphan*/  string; } ;
struct TYPE_12__ {TYPE_4__ id; TYPE_3__ points; int /*<<< orphan*/  memaddr; int /*<<< orphan*/  badge; int /*<<< orphan*/  desc; int /*<<< orphan*/  title; int /*<<< orphan*/  unofficial_count; TYPE_2__* patchdata; int /*<<< orphan*/  core_count; TYPE_1__ flags; } ;
typedef  TYPE_5__ rcheevos_readud_t ;
struct TYPE_13__ {unsigned int points; unsigned int id; void* memaddr; void* badge; void* description; void* title; } ;
typedef  TYPE_6__ rcheevos_racheevo_t ;
struct TYPE_9__ {TYPE_6__* unofficial; TYPE_6__* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEEVOS_FREE (void*) ; 
 void* rcheevos_dupstr (int /*<<< orphan*/ *) ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rcheevos_new_cheevo(rcheevos_readud_t* ud)
{
   rcheevos_racheevo_t* cheevo = NULL;
   unsigned flags             = (unsigned)strtol(ud->flags.string, NULL, 10);

   if (flags == 3)
      cheevo = ud->patchdata->core + ud->core_count++;
   else if (flags == 5)
      cheevo = ud->patchdata->unofficial + ud->unofficial_count++;
   else
      return 0;

   cheevo->title       = rcheevos_dupstr(&ud->title);
   cheevo->description = rcheevos_dupstr(&ud->desc);
   cheevo->badge       = rcheevos_dupstr(&ud->badge);
   cheevo->memaddr     = rcheevos_dupstr(&ud->memaddr);
   cheevo->points      = (unsigned)strtol(ud->points.string, NULL, 10);
   cheevo->id          = (unsigned)strtol(ud->id.string, NULL, 10);

   if (   !cheevo->title
       || !cheevo->description
       || !cheevo->badge
       || !cheevo->memaddr)
   {
      CHEEVOS_FREE(cheevo->title);
      CHEEVOS_FREE(cheevo->description);
      CHEEVOS_FREE(cheevo->badge);
      CHEEVOS_FREE(cheevo->memaddr);
      return -1;
   }

   return 0;
}
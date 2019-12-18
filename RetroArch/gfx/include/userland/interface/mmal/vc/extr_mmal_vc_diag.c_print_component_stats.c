#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct MMAL_VC_COMP_STATS_T {int state; char* name; int pid; int pool_mem_alloc_size; int /*<<< orphan*/  comp; } ;
struct TYPE_4__ {int list_size; int created; int destroyed; int destroying; int failed; struct MMAL_VC_COMP_STATS_T* component_list; } ;
struct TYPE_5__ {TYPE_1__ components; } ;
typedef  TYPE_2__ MMAL_VC_STATS_T ;

/* Variables and functions */
#define  MMAL_STATS_COMP_CREATED 130 
#define  MMAL_STATS_COMP_DESTROYED 129 
#define  MMAL_STATS_COMP_DESTROYING 128 
 int MMAL_STATS_COMP_IDLE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int print_component_stats(const MMAL_VC_STATS_T *stats)
{
   size_t i;
   if (stats->components.list_size > 64)
   {
      fprintf(stderr,"component array looks corrupt (list size %d\n",
            stats->components.list_size);
      goto fail;
   }
   printf("%d created, %d destroyed (%d destroying), %d create failures\n",
         stats->components.created,
         stats->components.destroyed,
         stats->components.destroying,
         stats->components.failed);

   for (i=0; i < stats->components.list_size; i++)
   {
      const struct MMAL_VC_COMP_STATS_T *cs = stats->components.component_list+i;
      const char *state;
      /* coverity[overrun-local] */
      if (cs->state != MMAL_STATS_COMP_IDLE)
      {
         switch (cs->state)
         {
            case MMAL_STATS_COMP_CREATED: state = "created"; break;
            case MMAL_STATS_COMP_DESTROYING: state = "destroying"; break;
            case MMAL_STATS_COMP_DESTROYED: state = "destroyed"; break;
            default: state = "corrupt"; break;
         }
         printf("%-32s: %s: pid %d address %p pool mem alloc size %d\n",
               cs->name, state, cs->pid, cs->comp, cs->pool_mem_alloc_size);
      }
   }
   return 0;
fail:
   return -1;
}
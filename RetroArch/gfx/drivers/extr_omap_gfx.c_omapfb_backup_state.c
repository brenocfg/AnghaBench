#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  omapfb_state_t ;
struct TYPE_5__ {TYPE_4__* saved_state; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ omapfb_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct TYPE_7__ {TYPE_3__ mi; int /*<<< orphan*/ * mem; TYPE_3__ si; TYPE_3__ pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBIOGET_VSCREENINFO ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  OMAPFB_QUERY_MEM ; 
 int /*<<< orphan*/  OMAPFB_QUERY_PLANE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 TYPE_4__* calloc (int,int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omapfb_backup_state(omapfb_data_t *pdata)
{
   void* mem = NULL;

   retro_assert(pdata->saved_state == NULL);

   pdata->saved_state = calloc(1, sizeof(omapfb_state_t));
   if (!pdata->saved_state) return -1;

   if (ioctl(pdata->fd, OMAPFB_QUERY_PLANE, &pdata->saved_state->pi) != 0)
   {
      RARCH_ERR("[video_omap]: backup layer (plane) failed\n");
      return -1;
   }

   if (ioctl(pdata->fd, OMAPFB_QUERY_MEM, &pdata->saved_state->mi) != 0)
   {
      RARCH_ERR("[video_omap]: backup layer (mem) failed\n");
      return -1;
   }

   if (ioctl(pdata->fd, FBIOGET_VSCREENINFO, &pdata->saved_state->si) != 0)
   {
      RARCH_ERR("[video_omap]: backup layer (screeninfo) failed\n");
      return -1;
   }

   pdata->saved_state->mem = malloc(pdata->saved_state->mi.size);
   mem = mmap(NULL, pdata->saved_state->mi.size, PROT_WRITE|PROT_READ,
         MAP_SHARED, pdata->fd, 0);
   if (pdata->saved_state->mem == NULL || mem == MAP_FAILED)
   {
      RARCH_ERR("[video_omap]: backup layer (mem backup) failed\n");
      munmap(mem, pdata->saved_state->mi.size);
      return -1;
   }
   memcpy(pdata->saved_state->mem, mem, pdata->saved_state->mi.size);
   munmap(mem, pdata->saved_state->mi.size);

   return 0;
}
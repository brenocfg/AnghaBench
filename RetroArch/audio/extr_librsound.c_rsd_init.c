#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  cond; void* cond_mutex; void* mutex; } ;
struct TYPE_7__ {int socket; int ctl_socket; } ;
struct TYPE_9__ {TYPE_2__ thread; void* cb_lock; TYPE_1__ conn; } ;
typedef  TYPE_3__ rsound_t ;

/* Variables and functions */
 int /*<<< orphan*/  CELL_SYSMODULE_NET ; 
 int* RSD_DEFAULT_HOST ; 
 int* RSD_DEFAULT_PORT ; 
 int /*<<< orphan*/  RSD_FORMAT ; 
 int /*<<< orphan*/  RSD_HOST ; 
 int /*<<< orphan*/  RSD_PORT ; 
 int RSD_S16_LE ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  cellSysmoduleLoadModule (int /*<<< orphan*/ ) ; 
 scalar_t__ init_count ; 
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsd_set_param (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  scond_new () ; 
 void* slock_new () ; 
 int /*<<< orphan*/  sys_net_initialize_network () ; 

int rsd_init(rsound_t** rsound)
{
   *rsound = calloc(1, sizeof(rsound_t));
   if ( *rsound == NULL )
      return -1;

   retro_assert(rsound != NULL);

   (*rsound)->conn.socket = -1;
   (*rsound)->conn.ctl_socket = -1;

   (*rsound)->thread.mutex = slock_new();
   (*rsound)->thread.cond_mutex = slock_new();
   (*rsound)->cb_lock = slock_new();
   (*rsound)->thread.cond = scond_new();

   // Assumes default of S16_LE samples.
   int format = RSD_S16_LE;
   rsd_set_param(*rsound, RSD_FORMAT, &format);

   rsd_set_param(*rsound, RSD_HOST, RSD_DEFAULT_HOST);
   rsd_set_param(*rsound, RSD_PORT, RSD_DEFAULT_PORT);

#ifdef __CELLOS_LV2__
   if (init_count == 0)
   {
      cellSysmoduleLoadModule(CELL_SYSMODULE_NET);
      sys_net_initialize_network();
      init_count++;
   }
#endif

   return 0;
}
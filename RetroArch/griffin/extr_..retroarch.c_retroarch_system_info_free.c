#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rarch_system_info_t ;
struct TYPE_13__ {int /*<<< orphan*/ * set_state; int /*<<< orphan*/ * callback; } ;
struct TYPE_11__ {int need_fullpath; int block_extract; int /*<<< orphan*/ * valid_extensions; int /*<<< orphan*/ * library_version; int /*<<< orphan*/ * library_name; } ;
struct TYPE_10__ {scalar_t__ num_descriptors; int /*<<< orphan*/ * descriptors; } ;
struct TYPE_9__ {void* data; scalar_t__ size; } ;
struct TYPE_8__ {void* data; scalar_t__ size; } ;
struct TYPE_12__ {TYPE_4__ info; TYPE_3__ mmaps; TYPE_2__ ports; TYPE_1__ subsystem; } ;

/* Variables and functions */
 TYPE_7__ audio_callback ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * runloop_frontend_key_event ; 
 int /*<<< orphan*/ * runloop_key_event ; 
 TYPE_5__ runloop_system ; 

__attribute__((used)) static void retroarch_system_info_free(void)
{
   if (runloop_system.subsystem.data)
      free(runloop_system.subsystem.data);
   runloop_system.subsystem.data = NULL;
   runloop_system.subsystem.size = 0;

   if (runloop_system.ports.data)
      free(runloop_system.ports.data);
   runloop_system.ports.data = NULL;
   runloop_system.ports.size = 0;

   if (runloop_system.mmaps.descriptors)
      free((void *)runloop_system.mmaps.descriptors);
   runloop_system.mmaps.descriptors          = NULL;
   runloop_system.mmaps.num_descriptors      = 0;

   runloop_key_event                         = NULL;
   runloop_frontend_key_event                = NULL;

   audio_callback.callback                   = NULL;
   audio_callback.set_state                  = NULL;

   runloop_system.info.library_name          = NULL;
   runloop_system.info.library_version       = NULL;
   runloop_system.info.valid_extensions      = NULL;
   runloop_system.info.need_fullpath         = false;
   runloop_system.info.block_extract         = false;

   memset(&runloop_system, 0, sizeof(rarch_system_info_t));
}
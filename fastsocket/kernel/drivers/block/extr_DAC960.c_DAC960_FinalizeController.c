#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ShutdownMonitoringTimer; scalar_t__ FirmwareType; scalar_t__ HardwareType; int /*<<< orphan*/  IO_Address; int /*<<< orphan*/  MonitoringTimer; int /*<<< orphan*/  queue_lock; scalar_t__ ControllerInitialized; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int /*<<< orphan*/  DAC960_DestroyAuxiliaryStructures (TYPE_1__*) ; 
 int /*<<< orphan*/  DAC960_DestroyProcEntries (TYPE_1__*) ; 
 int /*<<< orphan*/  DAC960_DetectCleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  DAC960_Notice (char*,TYPE_1__*) ; 
 scalar_t__ DAC960_PD_Controller ; 
 int /*<<< orphan*/  DAC960_UnregisterBlockDevice (TYPE_1__*) ; 
 scalar_t__ DAC960_V1_Controller ; 
 int /*<<< orphan*/  DAC960_V1_ExecuteType3 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAC960_V1_Flush ; 
 int /*<<< orphan*/  DAC960_V2_DeviceOperation (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAC960_V2_PauseDevice ; 
 int /*<<< orphan*/  DAC960_V2_RAID_Controller ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void DAC960_FinalizeController(DAC960_Controller_T *Controller)
{
  if (Controller->ControllerInitialized)
    {
      unsigned long flags;

      /*
       * Acquiring and releasing lock here eliminates
       * a very low probability race.
       *
       * The code below allocates controller command structures
       * from the free list without holding the controller lock.
       * This is safe assuming there is no other activity on
       * the controller at the time.
       * 
       * But, there might be a monitoring command still
       * in progress.  Setting the Shutdown flag while holding
       * the lock ensures that there is no monitoring command
       * in the interrupt handler currently, and any monitoring
       * commands that complete from this time on will NOT return
       * their command structure to the free list.
       */

      spin_lock_irqsave(&Controller->queue_lock, flags);
      Controller->ShutdownMonitoringTimer = 1;
      spin_unlock_irqrestore(&Controller->queue_lock, flags);

      del_timer_sync(&Controller->MonitoringTimer);
      if (Controller->FirmwareType == DAC960_V1_Controller)
	{
	  DAC960_Notice("Flushing Cache...", Controller);
	  DAC960_V1_ExecuteType3(Controller, DAC960_V1_Flush, 0);
	  DAC960_Notice("done\n", Controller);

	  if (Controller->HardwareType == DAC960_PD_Controller)
	      release_region(Controller->IO_Address, 0x80);
	}
      else
	{
	  DAC960_Notice("Flushing Cache...", Controller);
	  DAC960_V2_DeviceOperation(Controller, DAC960_V2_PauseDevice,
				    DAC960_V2_RAID_Controller);
	  DAC960_Notice("done\n", Controller);
	}
    }
  DAC960_UnregisterBlockDevice(Controller);
  DAC960_DestroyAuxiliaryStructures(Controller);
  DAC960_DestroyProcEntries(Controller);
  DAC960_DetectCleanup(Controller);
}
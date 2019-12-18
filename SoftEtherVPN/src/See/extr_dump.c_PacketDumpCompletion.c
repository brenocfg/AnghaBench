#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  UserEvent; int /*<<< orphan*/  IoStatus; int /*<<< orphan*/ * UserIosb; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PIRP ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_MORE_PROCESSING_REQUIRED ; 

__attribute__((used)) static NTSTATUS PacketDumpCompletion(PDEVICE_OBJECT DeviceObject,
                                PIRP Irp,
                                PVOID Context)
{

    // Copy the status information back into the "user" IOSB
    *Irp->UserIosb = Irp->IoStatus;
    
    // Wake up the mainline code
    KeSetEvent(Irp->UserEvent, 0, FALSE);
          
    return STATUS_MORE_PROCESSING_REQUIRED;
}
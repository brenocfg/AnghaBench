#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {int /*<<< orphan*/  performanceDataSize; int /*<<< orphan*/  performanceDataStart; int /*<<< orphan*/  efiRuntimeServicesVirtualPageStart; int /*<<< orphan*/  efiRuntimeServicesPageCount; int /*<<< orphan*/  efiRuntimeServicesPageStart; } ;
typedef  TYPE_1__ boot_args ;
struct TYPE_9__ {scalar_t__ bootArgs; } ;
struct TYPE_8__ {int cpu_hibernate; } ;
struct TYPE_7__ {int /*<<< orphan*/  performanceDataSize; int /*<<< orphan*/  performanceDataStart; int /*<<< orphan*/  runtimeVirtualPages; int /*<<< orphan*/  runtimePageCount; int /*<<< orphan*/  runtimePages; scalar_t__ processorFlags; } ;
typedef  TYPE_2__ IOHibernateImageHeader ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_5__ PE_state ; 
 TYPE_4__* cpu_datap (int /*<<< orphan*/ ) ; 

kern_return_t 
hibernate_processor_setup(IOHibernateImageHeader * header)
{
    boot_args * args = (boot_args *) PE_state.bootArgs;

    cpu_datap(0)->cpu_hibernate = 1;
    header->processorFlags = 0;

    header->runtimePages     = args->efiRuntimeServicesPageStart;
    header->runtimePageCount = args->efiRuntimeServicesPageCount;
    header->runtimeVirtualPages = args->efiRuntimeServicesVirtualPageStart;
    header->performanceDataStart = args->performanceDataStart;
    header->performanceDataSize = args->performanceDataSize;

    return (KERN_SUCCESS);
}
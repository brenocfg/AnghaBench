#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ibm_struct {TYPE_1__* acpi; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  (* notify ) (struct ibm_struct*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ TPACPI_LIFE_RUNNING ; 
 int /*<<< orphan*/  stub1 (struct ibm_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ tpacpi_lifecycle ; 

__attribute__((used)) static void dispatch_acpi_notify(acpi_handle handle, u32 event, void *data)
{
	struct ibm_struct *ibm = data;

	if (tpacpi_lifecycle != TPACPI_LIFE_RUNNING)
		return;

	if (!ibm || !ibm->acpi || !ibm->acpi->notify)
		return;

	ibm->acpi->notify(ibm, event);
}
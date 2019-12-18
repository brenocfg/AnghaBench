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
struct TYPE_2__ {scalar_t__ status; scalar_t__ done; } ;
union acpi_smb_status {TYPE_1__ fields; int /*<<< orphan*/  raw; } ;
struct acpi_smb_hc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SMB_STATUS ; 
 scalar_t__ SMBUS_OK ; 
 int /*<<< orphan*/  smb_hc_read (struct acpi_smb_hc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int smb_check_done(struct acpi_smb_hc *hc)
{
	union acpi_smb_status status = {.raw = 0};
	smb_hc_read(hc, ACPI_SMB_STATUS, &status.raw);
	return status.fields.done && (status.fields.status == SMBUS_OK);
}
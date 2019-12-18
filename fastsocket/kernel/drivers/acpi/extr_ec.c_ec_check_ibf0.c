#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct acpi_ec {int dummy; } ;

/* Variables and functions */
 int ACPI_EC_FLAG_IBF ; 
 int acpi_ec_read_status (struct acpi_ec*) ; 

__attribute__((used)) static int ec_check_ibf0(struct acpi_ec *ec)
{
	u8 status = acpi_ec_read_status(ec);
	return (status & ACPI_EC_FLAG_IBF) == 0;
}
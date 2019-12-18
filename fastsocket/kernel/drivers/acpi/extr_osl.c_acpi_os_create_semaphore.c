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
typedef  int /*<<< orphan*/  u32 ;
struct semaphore {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/ **** acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_MUTEX ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 struct semaphore* acpi_os_allocate (int) ; 
 int /*<<< orphan*/  memset (struct semaphore*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sema_init (struct semaphore*,int /*<<< orphan*/ ) ; 

acpi_status
acpi_os_create_semaphore(u32 max_units, u32 initial_units, acpi_handle * handle)
{
	struct semaphore *sem = NULL;

	sem = acpi_os_allocate(sizeof(struct semaphore));
	if (!sem)
		return AE_NO_MEMORY;
	memset(sem, 0, sizeof(struct semaphore));

	sema_init(sem, initial_units);

	*handle = (acpi_handle *) sem;

	ACPI_DEBUG_PRINT((ACPI_DB_MUTEX, "Creating semaphore[%p|%d].\n",
			  *handle, initial_units));

	return AE_OK;
}
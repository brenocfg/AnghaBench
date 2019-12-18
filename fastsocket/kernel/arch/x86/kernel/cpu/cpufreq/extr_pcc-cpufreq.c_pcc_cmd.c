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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CMD_COMPLETE ; 
 int POLL_LOOPS ; 
 int /*<<< orphan*/  acpi_read (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_write (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  doorbell ; 
 int doorbell_preserve ; 
 int doorbell_write ; 
 int ioread16 (int /*<<< orphan*/ *) ; 
 TYPE_1__* pcch_hdr ; 

__attribute__((used)) static inline void pcc_cmd(void)
{
	u64 doorbell_value;
	int i;

	acpi_read(&doorbell_value, &doorbell);
	acpi_write((doorbell_value & doorbell_preserve) | doorbell_write,
		   &doorbell);

	for (i = 0; i < POLL_LOOPS; i++) {
		if (ioread16(&pcch_hdr->status) & CMD_COMPLETE)
			break;
	}
}
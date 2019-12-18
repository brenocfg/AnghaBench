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
struct TYPE_2__ {int /*<<< orphan*/  dest_logical; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DEST_ALLINC ; 
 int NMI_VECTOR ; 
 int /*<<< orphan*/  __default_send_IPI_shortcut (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  flat_send_IPI_mask (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void flat_send_IPI_all(int vector)
{
	if (vector == NMI_VECTOR) {
		flat_send_IPI_mask(cpu_online_mask, vector);
	} else {
		__default_send_IPI_shortcut(APIC_DEST_ALLINC,
					    vector, apic->dest_logical);
	}
}
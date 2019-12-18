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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA32_BIOS_UPDT_TRIG ; 
 TYPE_1__* global_update ; 
 int /*<<< orphan*/  wrmsr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_microcode(void)
{
	/* SDM Example 9-8 code shows that we load the
	 * address of the UpdateData within the microcode blob,
	 * not the address of the header.
	 */
	wrmsr64(IA32_BIOS_UPDT_TRIG, (uint64_t)(uintptr_t)&global_update->data);
}
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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_CM_CMASK ; 
 int /*<<< orphan*/  CONF_CM_UNCACHED ; 
#define  CPU_VR4122 130 
#define  CPU_VR4131 129 
#define  CPU_VR4133 128 
 int /*<<< orphan*/  PMUCNT2REG ; 
 int /*<<< orphan*/  SOFTRST ; 
 int ST0_BEV ; 
 int ST0_ERL ; 
 int /*<<< orphan*/  change_c0_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int current_cpu_type () ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  pmu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_c0_status (int) ; 
 int /*<<< orphan*/  write_c0_wired (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void software_reset(void)
{
	uint16_t pmucnt2;

	switch (current_cpu_type()) {
	case CPU_VR4122:
	case CPU_VR4131:
	case CPU_VR4133:
		pmucnt2 = pmu_read(PMUCNT2REG);
		pmucnt2 |= SOFTRST;
		pmu_write(PMUCNT2REG, pmucnt2);
		break;
	default:
		set_c0_status(ST0_BEV | ST0_ERL);
		change_c0_config(CONF_CM_CMASK, CONF_CM_UNCACHED);
		flush_cache_all();
		write_c0_wired(0);
		__asm__("jr     %0"::"r"(0xbfc00000));
		break;
	}
}
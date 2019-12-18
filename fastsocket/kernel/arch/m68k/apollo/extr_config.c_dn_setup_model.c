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

/* Variables and functions */
#define  APOLLO_DN3000 133 
#define  APOLLO_DN3010 132 
#define  APOLLO_DN3500 131 
#define  APOLLO_DN4000 130 
#define  APOLLO_DN4500 129 
#define  APOLLO_UNKNOWN 128 
 int /*<<< orphan*/  SAU7_CPUCTRL ; 
 int /*<<< orphan*/  SAU7_PICA ; 
 int /*<<< orphan*/  SAU7_PICB ; 
 int /*<<< orphan*/  SAU7_RTC_PHYSADDR ; 
 int /*<<< orphan*/  SAU7_SIO01_PHYSADDR ; 
 int /*<<< orphan*/  SAU7_SIO23_PHYSADDR ; 
 int /*<<< orphan*/  SAU7_TIMER ; 
 int /*<<< orphan*/  SAU8_CPUCTRL ; 
 int /*<<< orphan*/  SAU8_PICA ; 
 int /*<<< orphan*/  SAU8_PICB ; 
 int /*<<< orphan*/  SAU8_RTC_PHYSADDR ; 
 int /*<<< orphan*/  SAU8_SIO01_PHYSADDR ; 
 int /*<<< orphan*/  SAU8_TIMER ; 
 int apollo_model ; 
 int /*<<< orphan*/ * apollo_models ; 
 int /*<<< orphan*/  cpuctrl_physaddr ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pica_physaddr ; 
 int /*<<< orphan*/  picb_physaddr ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  rtc_physaddr ; 
 int /*<<< orphan*/  sio01_physaddr ; 
 int /*<<< orphan*/  sio23_physaddr ; 
 int /*<<< orphan*/  timer_physaddr ; 

void dn_setup_model(void) {


	printk("Apollo hardware found: ");
	printk("[%s]\n", apollo_models[apollo_model - APOLLO_DN3000]);

	switch(apollo_model) {
		case APOLLO_UNKNOWN:
			panic("Unknown apollo model");
			break;
		case APOLLO_DN3000:
		case APOLLO_DN3010:
			sio01_physaddr=SAU8_SIO01_PHYSADDR;
			rtc_physaddr=SAU8_RTC_PHYSADDR;
			pica_physaddr=SAU8_PICA;
			picb_physaddr=SAU8_PICB;
			cpuctrl_physaddr=SAU8_CPUCTRL;
			timer_physaddr=SAU8_TIMER;
			break;
		case APOLLO_DN4000:
			sio01_physaddr=SAU7_SIO01_PHYSADDR;
			sio23_physaddr=SAU7_SIO23_PHYSADDR;
			rtc_physaddr=SAU7_RTC_PHYSADDR;
			pica_physaddr=SAU7_PICA;
			picb_physaddr=SAU7_PICB;
			cpuctrl_physaddr=SAU7_CPUCTRL;
			timer_physaddr=SAU7_TIMER;
			break;
		case APOLLO_DN4500:
			panic("Apollo model not yet supported");
			break;
		case APOLLO_DN3500:
			sio01_physaddr=SAU7_SIO01_PHYSADDR;
			sio23_physaddr=SAU7_SIO23_PHYSADDR;
			rtc_physaddr=SAU7_RTC_PHYSADDR;
			pica_physaddr=SAU7_PICA;
			picb_physaddr=SAU7_PICB;
			cpuctrl_physaddr=SAU7_CPUCTRL;
			timer_physaddr=SAU7_TIMER;
			break;
		default:
			panic("Undefined apollo model");
			break;
	}


}
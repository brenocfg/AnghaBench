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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {void* dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  csr_int_status ; 
 scalar_t__ readb (int /*<<< orphan*/ ) ; 
 TYPE_1__ zt5550_hpc ; 

__attribute__((used)) static int zt5550_hc_check_irq(void *dev_id)
{
	int ret;
	u8 reg;

	ret = 0;
	if(dev_id == zt5550_hpc.dev_id) {
		reg = readb(csr_int_status);
		if(reg)
			ret = 1;
	}
	return ret;
}
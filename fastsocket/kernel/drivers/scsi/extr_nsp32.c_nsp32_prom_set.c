#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int BaseAddress; } ;
typedef  TYPE_1__ nsp32_hw_data ;

/* Variables and functions */
 int /*<<< orphan*/  SERIAL_ROM_CTL ; 
 int nsp32_index_read1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_index_write1 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void nsp32_prom_set(nsp32_hw_data *data, int bit, int val)
{
	int base = data->BaseAddress;
	int tmp;

	tmp = nsp32_index_read1(base, SERIAL_ROM_CTL);

	if (val == 0) {
		tmp &= ~bit;
	} else {
		tmp |=  bit;
	}

	nsp32_index_write1(base, SERIAL_ROM_CTL, tmp);

	udelay(10);
}
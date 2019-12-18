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
typedef  int u32 ;
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_I2C ; 
 int cx_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx8800_bit_getscl(void *data)
{
	struct cx88_core *core = data;
	u32 state;

	state = cx_read(MO_I2C);
	return state & 0x02 ? 1 : 0;
}
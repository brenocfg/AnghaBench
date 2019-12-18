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
struct cx8802_dev {struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_GP0_IO ; 
 int cx_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vp3054_bit_getsda(void *data)
{
	struct cx8802_dev *dev = data;
	struct cx88_core *core = dev->core;
	u32 state;

	state = cx_read(MO_GP0_IO);
	return (state & 0x02) ? 1 : 0;
}
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
struct sym_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  T93C46_Read_Word (struct sym_device*,unsigned short*,unsigned char*) ; 
 int /*<<< orphan*/  T93C46_Send_Command (struct sym_device*,int,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  T93C46_Stop (struct sym_device*,unsigned char*) ; 

__attribute__((used)) static int T93C46_Read_Data(struct sym_device *np, unsigned short *data,
		int len, unsigned char *gpreg)
{
	int x;

	for (x = 0; x < len; x++)  {
		unsigned char read_bit;
		/* output read command and address */
		T93C46_Send_Command(np, 0x180 | x, &read_bit, gpreg);
		if (read_bit & 0x01)
			return 1; /* Bad */
		T93C46_Read_Word(np, &data[x], gpreg);
		T93C46_Stop(np, gpreg);
	}

	return 0;
}
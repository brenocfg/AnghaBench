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
typedef  int u8 ;
typedef  int u32 ;
struct sisusb_usb_data {int dummy; } ;

/* Variables and functions */
 int sisusb_check_rbc (struct sisusb_usb_data*,int*,int,int) ; 

__attribute__((used)) static int
sisusb_check_ranks(struct sisusb_usb_data *sisusb, int *iret, int rankno,
					int idx, int bw, const u8 rtype[][5])
{
	int ret = 0, i, i2ret;
	u32 inc;

	*iret = 0;

	for (i = rankno; i >= 1; i--) {
		inc = 1 << (rtype[idx][2] +
			    rtype[idx][1] +
			    rtype[idx][0] +
			    bw / 64 + i);
		ret |= sisusb_check_rbc(sisusb, &i2ret, inc, 2);
		if (!i2ret)
			return ret;
	}

	inc = 1 << (rtype[idx][2] + bw / 64 + 2);
	ret |= sisusb_check_rbc(sisusb, &i2ret, inc, 4);
	if (!i2ret)
		return ret;

	inc = 1 << (10 + bw / 64);
	ret |= sisusb_check_rbc(sisusb, &i2ret, inc, 2);
	if (!i2ret)
		return ret;

	*iret = 1;
	return ret;
}
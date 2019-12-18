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
struct soc_mbus_pixelfmt {int packing; int bits_per_sample; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
#define  SOC_MBUS_PACKING_2X8_PADHI 131 
#define  SOC_MBUS_PACKING_2X8_PADLO 130 
#define  SOC_MBUS_PACKING_EXTEND16 129 
#define  SOC_MBUS_PACKING_NONE 128 

s32 soc_mbus_bytes_per_line(u32 width, const struct soc_mbus_pixelfmt *mf)
{
	switch (mf->packing) {
	case SOC_MBUS_PACKING_NONE:
		return width * mf->bits_per_sample / 8;
	case SOC_MBUS_PACKING_2X8_PADHI:
	case SOC_MBUS_PACKING_2X8_PADLO:
	case SOC_MBUS_PACKING_EXTEND16:
		return width * 2;
	}
	return -EINVAL;
}
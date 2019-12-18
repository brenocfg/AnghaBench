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
typedef  int /*<<< orphan*/  u32 ;
struct cx231xx_dmaqueue {int last_sav; } ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
#define  SAV_VBI_FIELD1 129 
#define  SAV_VBI_FIELD2 128 
 int /*<<< orphan*/  cx231xx_copy_vbi_line (struct cx231xx*,struct cx231xx_dmaqueue*,int*,int /*<<< orphan*/ ,int) ; 

u32 cx231xx_get_vbi_line(struct cx231xx *dev, struct cx231xx_dmaqueue *dma_q,
			 u8 sav_eav, u8 *p_buffer, u32 buffer_size)
{
	u32 bytes_copied = 0;
	int current_field = -1;

	switch (sav_eav) {

	case SAV_VBI_FIELD1:
		current_field = 1;
		break;

	case SAV_VBI_FIELD2:
		current_field = 2;
		break;
	default:
		break;
	}

	if (current_field < 0)
		return bytes_copied;

	dma_q->last_sav = sav_eav;

	bytes_copied =
	    cx231xx_copy_vbi_line(dev, dma_q, p_buffer, buffer_size,
				  current_field);

	return bytes_copied;
}
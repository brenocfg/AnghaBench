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
typedef  size_t u8 ;
typedef  int u32 ;
struct vpif_vbi_params {int hstart0; int vstart0; int hstart1; int vstart1; int hsize0; int vsize0; int hsize1; int vsize1; } ;
struct TYPE_2__ {int /*<<< orphan*/  vanc1_size; int /*<<< orphan*/  vanc0_size; int /*<<< orphan*/  vanc1_strt; int /*<<< orphan*/  vanc0_strt; } ;

/* Variables and functions */
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* vpifregs ; 

void vpif_set_vbi_display_params(struct vpif_vbi_params *vbiparams,
				u8 channel_id)
{
	u32 value;

	value = 0x3F8 & (vbiparams->hstart0);
	value |= 0x3FFFFFF & ((vbiparams->vstart0) << 16);
	regw(value, vpifregs[channel_id].vanc0_strt);

	value = 0x3F8 & (vbiparams->hstart1);
	value |= 0x3FFFFFF & ((vbiparams->vstart1) << 16);
	regw(value, vpifregs[channel_id].vanc1_strt);

	value = 0x3F8 & (vbiparams->hsize0);
	value |= 0x3FFFFFF & ((vbiparams->vsize0) << 16);
	regw(value, vpifregs[channel_id].vanc0_size);

	value = 0x3F8 & (vbiparams->hsize1);
	value |= 0x3FFFFFF & ((vbiparams->vsize1) << 16);
	regw(value, vpifregs[channel_id].vanc1_size);

}
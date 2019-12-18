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
typedef  int uint ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct brcms_hardware {int dummy; } ;

/* Variables and functions */
 int brcms_b_read_objmem (struct brcms_hardware*,int,int /*<<< orphan*/ ) ; 

void
brcms_b_copyfrom_objmem(struct brcms_hardware *wlc_hw, uint offset, void *buf,
			 int len, u32 sel)
{
	u16 v;
	u8 *p = (u8 *) buf;
	int i;

	if (len <= 0 || (offset & 1) || (len & 1))
		return;

	for (i = 0; i < len; i += 2) {
		v = brcms_b_read_objmem(wlc_hw, offset + i, sel);
		p[i] = v & 0xFF;
		p[i + 1] = (v >> 8) & 0xFF;
	}
}
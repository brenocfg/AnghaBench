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
struct cmdif {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ SEND_SMEM (struct cmdif*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SEND_WMEM (struct cmdif*,int,int) ; 
 int atoh (unsigned char const*,int) ; 

__attribute__((used)) static int senddata(struct cmdif *cif, const unsigned char *in, u32 offset)
{
	u32 addr;
	u32 data;
	u32 i;
	const unsigned char *p;

	i = atoh(&in[1], 2);
	addr = offset + atoh(&in[3], 4);
	if (SEND_SMEM(cif, 0, addr) != 0)
		return -EACCES;
	p = in + 9;
	while (i) {
		data = atoh(p, 8);
		if (SEND_WMEM(cif, 2,
			      ((data & 0x0f0f0f0f) << 4) | ((data & 0xf0f0f0f0)
							    >> 4)))
			return -EACCES;
		i -= 4;
		p += 8;
	}
	return 0;
}
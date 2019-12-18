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
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv04_graph_set_ctx1 (struct nouveau_object*,int,int) ; 
 int nv_ro32 (struct nouveau_object*,int) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_object*,int,int) ; 

__attribute__((used)) static void
nv04_graph_set_ctx_val(struct nouveau_object *object, u32 mask, u32 value)
{
	int class, op, valid = 1;
	u32 tmp, ctx1;

	ctx1 = nv_ro32(object, 0x00);
	class = ctx1 & 0xff;
	op = (ctx1 >> 15) & 7;

	tmp = nv_ro32(object, 0x0c);
	tmp &= ~mask;
	tmp |= value;
	nv_wo32(object, 0x0c, tmp);

	/* check for valid surf2d/surf_dst/surf_color */
	if (!(tmp & 0x02000000))
		valid = 0;
	/* check for valid surf_src/surf_zeta */
	if ((class == 0x1f || class == 0x48) && !(tmp & 0x04000000))
		valid = 0;

	switch (op) {
	/* SRCCOPY_AND, SRCCOPY: no extra objects required */
	case 0:
	case 3:
		break;
	/* ROP_AND: requires pattern and rop */
	case 1:
		if (!(tmp & 0x18000000))
			valid = 0;
		break;
	/* BLEND_AND: requires beta1 */
	case 2:
		if (!(tmp & 0x20000000))
			valid = 0;
		break;
	/* SRCCOPY_PREMULT, BLEND_PREMULT: beta4 required */
	case 4:
	case 5:
		if (!(tmp & 0x40000000))
			valid = 0;
		break;
	}

	nv04_graph_set_ctx1(object, 0x01000000, valid << 24);
}
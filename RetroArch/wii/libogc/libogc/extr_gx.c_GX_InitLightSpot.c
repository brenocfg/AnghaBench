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
struct __gx_litobj {float a0; float a1; float a2; } ;
typedef  float f32 ;
typedef  int /*<<< orphan*/  GXLightObj ;

/* Variables and functions */
#define  GX_SP_COS 134 
#define  GX_SP_COS2 133 
#define  GX_SP_FLAT 132 
#define  GX_SP_OFF 131 
#define  GX_SP_RING1 130 
#define  GX_SP_RING2 129 
#define  GX_SP_SHARP 128 
 float M_PI ; 
 float cosf (float) ; 

void GX_InitLightSpot(GXLightObj *lit_obj,f32 cut_off,u8 spotfn)
{
	f32 r,d,cr,a0,a1,a2;
	struct __gx_litobj *lit = (struct __gx_litobj*)lit_obj;

	if(cut_off<0.0f ||	cut_off>90.0f) spotfn = GX_SP_OFF;

	r = (cut_off*M_PI)/180.0f;
	cr = cosf(r);

	switch(spotfn) {
		case GX_SP_FLAT:
			a0 = -1000.0f*cr;
			a1 = 1000.0f;
			a2 = 0.0f;
			break;
		case GX_SP_COS:
			a0 = -cr/(1.0f-cr);
			a1 = 1.0f/(1.0f-cr);
			a2 = 0.0f;
			break;
		case GX_SP_COS2:
			a0 = 0.0f;
			a1 = -cr/(1.0f-cr);
			a2 = 1.0f/(1.0f-cr);
			break;
		case GX_SP_SHARP:
			d = (1.0f-cr)*(1.0f-cr);
			a0 = cr*(cr-2.0f);
			a1 = 2.0f/d;
			a2 = -1.0/d;
			break;
		case GX_SP_RING1:
			d = (1.0f-cr)*(1.0f-cr);
			a0 = -4.0f*cr/d;
			a1 = 4.0f*(1.0f+cr)/d;
			a2 = -4.0f/d;
			break;
		case GX_SP_RING2:
			d = (1.0f-cr)*(1.0f-cr);
			a0 = 1.0f-2.0f*cr*cr/d;
			a1 = 4.0f*cr/d;
			a2 = -2.0f/d;
			break;
		case GX_SP_OFF:
		default:
			a0 = 1.0f;
			a1 = 0.0f;
			a2 = 0.0f;
			break;
	}

	lit->a0 = a0;
	lit->a1 = a1;
	lit->a2 = a2;
}
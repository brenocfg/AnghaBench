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
struct __gx_litobj {float k0; float k1; float k2; } ;
typedef  float f32 ;
typedef  int /*<<< orphan*/  GXLightObj ;

/* Variables and functions */
#define  GX_DA_GENTLE 131 
#define  GX_DA_MEDIUM 130 
#define  GX_DA_OFF 129 
#define  GX_DA_STEEP 128 

void GX_InitLightDistAttn(GXLightObj *lit_obj,f32 ref_dist,f32 ref_brite,u8 dist_fn)
{
	f32 k0,k1,k2;
	struct __gx_litobj *lit = (struct __gx_litobj*)lit_obj;

	if(ref_dist<0.0f ||
		ref_brite<0.0f || ref_brite>=1.0f) dist_fn = GX_DA_OFF;

	switch(dist_fn) {
		case GX_DA_GENTLE:
			k0 = 1.0f;
			k1 = (1.0f-ref_brite)/(ref_brite*ref_dist);
			k2 = 0.0f;
			break;
		case GX_DA_MEDIUM:
			k0 = 1.0f;
			k1 = 0.5f*(1.0f-ref_brite)/(ref_brite*ref_dist);
			k2 = 0.5f*(1.0f-ref_brite)/(ref_brite*ref_dist*ref_dist);
			break;
		case GX_DA_STEEP:
			k0 = 1.0f;
			k1 = 0.0f;
			k2 = (1.0f-ref_brite)/(ref_brite*ref_dist*ref_dist);
			break;
		case GX_DA_OFF:
		default:
			k0 = 1.0f;
			k1 = 0.0f;
			k2 = 0.0f;
			break;
	}

	lit->k0 = k0;
	lit->k1 = k1;
	lit->k2 = k2;
}
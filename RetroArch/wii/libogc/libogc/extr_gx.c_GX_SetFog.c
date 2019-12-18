#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct ieee32 {float f; int i; } ;
typedef  float f32 ;
struct TYPE_3__ {int r; int g; int b; } ;
typedef  TYPE_1__ GXColor ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTL (int,int,int) ; 
 int _SHIFTR (int,int,int) ; 

void GX_SetFog(u8 type,f32 startz,f32 endz,f32 nearz,f32 farz,GXColor col)
{
    f32 A, B, B_mant, C, A_f;
    u32 b_expn, b_m, a_hex, c_hex,val,proj = 0;
	union ieee32 { f32 f; u32 i; } v;

  	proj = _SHIFTR(type,3,1);

	// Calculate constants a, b, and c (TEV HW requirements).
	if(proj) { // Orthographic Fog Type
		if((farz==nearz) || (endz==startz)) {
			// take care of the odd-ball case.
			A_f = 0.0f;
			C = 0.0f;
		} else {
			A = 1.0f/(endz-startz);
			A_f = (farz-nearz) * A;
			C = (startz-nearz) * A;
		}

		b_expn	= 0;
		b_m		= 0;
	} else { // Perspective Fog Type
	  // Calculate constants a, b, and c (TEV HW requirements).
		if((farz==nearz) || (endz==startz)) {
			// take care of the odd-ball case.
			A = 0.0f;
			B = 0.5f;
			C = 0.0f;
		} else {
			A = (farz*nearz)/((farz-nearz)*(endz-startz));
			B = farz/(farz-nearz);
			C = startz/(endz-startz);
		}

		B_mant = B;
		b_expn = 1;
		while(B_mant>1.0f) {
			B_mant /= 2.0f;
			b_expn++;
		}

		while((B_mant>0.0f) && (B_mant<0.5f)) {
			B_mant *= 2.0f;
			b_expn--;
		}

		A_f   = A/(1<<(b_expn));
		b_m   = (u32)(B_mant * 8388638.0f);
	}
	v.f = A_f;
    a_hex = v.i;

	v.f = C;
    c_hex = v.i;

	val = 0xee000000|(_SHIFTR(a_hex,12,20));
	GX_LOAD_BP_REG(val);

	val = 0xef000000|(b_m&0x00ffffff);
	GX_LOAD_BP_REG(val);

	val = 0xf0000000|(b_expn&0x1f);
	GX_LOAD_BP_REG(val);

	val = 0xf1000000|(_SHIFTL(type,21,3))|(_SHIFTL(proj,20,1))|(_SHIFTR(c_hex,12,20));
	GX_LOAD_BP_REG(val);

	val = 0xf2000000|(_SHIFTL(col.r,16,8))|(_SHIFTL(col.g,8,8))|(col.b&0xff);
	GX_LOAD_BP_REG(val);
}
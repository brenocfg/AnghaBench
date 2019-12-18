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
struct __gx_litobj {float px; float py; float pz; float nx; float ny; float nz; } ;
typedef  float f32 ;
typedef  int /*<<< orphan*/  GXLightObj ;

/* Variables and functions */
 float LARGE_NUMBER ; 
 float sqrtf (float) ; 

void GX_InitSpecularDir(GXLightObj *lit_obj,f32 nx,f32 ny,f32 nz)
{
    f32 px, py, pz;
    f32 hx, hy, hz, mag;
	struct __gx_litobj *lit = (struct __gx_litobj*)lit_obj;

    // Compute half-angle vector
    hx  = -nx;
    hy  = -ny;
    hz  = (-nz + 1.0f);
	mag = ((hx * hx) + (hy * hy) + (hz * hz));
	if(mag!=0.0f) mag = 1.0f / sqrtf(mag);

    hx *= mag;
    hy *= mag;
    hz *= mag;

    px  = (nx * LARGE_NUMBER);
    py  = (ny * LARGE_NUMBER);
    pz  = (nz * LARGE_NUMBER);

	lit->px = px;
	lit->py = py;
	lit->pz = pz;
	lit->nx = hx;
	lit->ny = hy;
	lit->nz = hz;
}
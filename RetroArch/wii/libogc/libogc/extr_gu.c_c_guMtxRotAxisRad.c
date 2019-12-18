#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float x; float y; float z; } ;
typedef  TYPE_1__ guVector ;
typedef  float f32 ;
typedef  float** Mtx ;

/* Variables and functions */
 int /*<<< orphan*/  c_guVecNormalize (TYPE_1__*) ; 
 float cosf (float) ; 
 float sinf (float) ; 

void c_guMtxRotAxisRad(Mtx mt,guVector *axis,f32 rad)
{
	f32 s,c;
	f32 t;
	f32 x,y,z;
	f32 xSq,ySq,zSq;

	s = sinf(rad);
	c = cosf(rad);
	t = 1.0f-c;

	c_guVecNormalize(axis);

	x = axis->x;
	y = axis->y;
	z = axis->z;

	xSq = x*x;
	ySq = y*y;
	zSq = z*z;

    mt[0][0] = ( t * xSq )   + ( c );
    mt[0][1] = ( t * x * y ) - ( s * z );
    mt[0][2] = ( t * x * z ) + ( s * y );
    mt[0][3] =    0.0f;

    mt[1][0] = ( t * x * y ) + ( s * z );
    mt[1][1] = ( t * ySq )   + ( c );
    mt[1][2] = ( t * y * z ) - ( s * x );
    mt[1][3] =    0.0f;

    mt[2][0] = ( t * x * z ) - ( s * y );
    mt[2][1] = ( t * y * z ) + ( s * x );
    mt[2][2] = ( t * zSq )   + ( c );
    mt[2][3] =    0.0f;

}
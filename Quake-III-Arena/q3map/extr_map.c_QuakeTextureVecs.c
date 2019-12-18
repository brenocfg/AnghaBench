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
typedef  int vec_t ;
typedef  int* vec3_t ;
typedef  int /*<<< orphan*/  plane_t ;

/* Variables and functions */
 int Q_PI ; 
 int /*<<< orphan*/  TextureAxisFromPlane (int /*<<< orphan*/ *,int*,int*) ; 
 int cos (int) ; 
 int sin (int) ; 

void QuakeTextureVecs( 	plane_t *plane, vec_t shift[2], vec_t rotate, vec_t scale[2],
					  vec_t mappingVecs[2][4] ) {
 
	vec3_t	vecs[2];
	int		sv, tv;
	vec_t	ang, sinv, cosv;
	vec_t	ns, nt;
	int		i, j;

	TextureAxisFromPlane(plane, vecs[0], vecs[1]);

	if (!scale[0])
		scale[0] = 1;
	if (!scale[1])
		scale[1] = 1;

	// rotate axis
	if (rotate == 0)
		{ sinv = 0 ; cosv = 1; }
	else if (rotate == 90)
		{ sinv = 1 ; cosv = 0; }
	else if (rotate == 180)
		{ sinv = 0 ; cosv = -1; }
	else if (rotate == 270)
		{ sinv = -1 ; cosv = 0; }
	else
	{	
		ang = rotate / 180 * Q_PI;
		sinv = sin(ang);
		cosv = cos(ang);
	}

	if (vecs[0][0])
		sv = 0;
	else if (vecs[0][1])
		sv = 1;
	else
		sv = 2;
				
	if (vecs[1][0])
		tv = 0;
	else if (vecs[1][1])
		tv = 1;
	else
		tv = 2;
					
	for (i=0 ; i<2 ; i++) {
		ns = cosv * vecs[i][sv] - sinv * vecs[i][tv];
		nt = sinv * vecs[i][sv] +  cosv * vecs[i][tv];
		vecs[i][sv] = ns;
		vecs[i][tv] = nt;
	}

	for (i=0 ; i<2 ; i++)
		for (j=0 ; j<3 ; j++)
			mappingVecs[i][j] = vecs[i][j] / scale[i];

	mappingVecs[0][3] = shift[0];
	mappingVecs[1][3] = shift[1];
}
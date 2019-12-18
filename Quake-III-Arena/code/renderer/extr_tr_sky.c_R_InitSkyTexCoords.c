#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_3__ {int zFar; } ;
struct TYPE_4__ {TYPE_1__ viewParms; } ;

/* Variables and functions */
 int DotProduct (int*,int*) ; 
 int HALF_SKY_SUBDIVISIONS ; 
 int /*<<< orphan*/  MakeSkyVec (int,int,int,int /*<<< orphan*/ *,int*) ; 
 float Q_acos (int) ; 
 int SKY_SUBDIVISIONS ; 
 int SQR (float) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorScale (int*,float,int*) ; 
 TYPE_2__ backEnd ; 
 float**** s_cloudTexCoords ; 
 float*** s_cloudTexP ; 
 int sqrt (int) ; 

void R_InitSkyTexCoords( float heightCloud )
{
	int i, s, t;
	float radiusWorld = 4096;
	float p;
	float sRad, tRad;
	vec3_t skyVec;
	vec3_t v;

	// init zfar so MakeSkyVec works even though
	// a world hasn't been bounded
	backEnd.viewParms.zFar = 1024;

	for ( i = 0; i < 6; i++ )
	{
		for ( t = 0; t <= SKY_SUBDIVISIONS; t++ )
		{
			for ( s = 0; s <= SKY_SUBDIVISIONS; s++ )
			{
				// compute vector from view origin to sky side integral point
				MakeSkyVec( ( s - HALF_SKY_SUBDIVISIONS ) / ( float ) HALF_SKY_SUBDIVISIONS, 
							( t - HALF_SKY_SUBDIVISIONS ) / ( float ) HALF_SKY_SUBDIVISIONS, 
							i, 
							NULL,
							skyVec );

				// compute parametric value 'p' that intersects with cloud layer
				p = ( 1.0f / ( 2 * DotProduct( skyVec, skyVec ) ) ) *
					( -2 * skyVec[2] * radiusWorld + 
					   2 * sqrt( SQR( skyVec[2] ) * SQR( radiusWorld ) + 
					             2 * SQR( skyVec[0] ) * radiusWorld * heightCloud +
								 SQR( skyVec[0] ) * SQR( heightCloud ) + 
								 2 * SQR( skyVec[1] ) * radiusWorld * heightCloud +
								 SQR( skyVec[1] ) * SQR( heightCloud ) + 
								 2 * SQR( skyVec[2] ) * radiusWorld * heightCloud +
								 SQR( skyVec[2] ) * SQR( heightCloud ) ) );

				s_cloudTexP[i][t][s] = p;

				// compute intersection point based on p
				VectorScale( skyVec, p, v );
				v[2] += radiusWorld;

				// compute vector from world origin to intersection point 'v'
				VectorNormalize( v );

				sRad = Q_acos( v[0] );
				tRad = Q_acos( v[1] );

				s_cloudTexCoords[i][t][s][0] = sRad;
				s_cloudTexCoords[i][t][s][1] = tRad;
			}
		}
	}
}
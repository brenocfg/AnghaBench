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
struct image_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_Bind (struct image_s*) ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int const HALF_SKY_SUBDIVISIONS ; 
 int /*<<< orphan*/  qglBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnd () ; 
 int /*<<< orphan*/  qglTexCoord2fv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglVertex3fv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** s_skyPoints ; 
 int /*<<< orphan*/ ** s_skyTexCoords ; 

__attribute__((used)) static void DrawSkySide( struct image_s *image, const int mins[2], const int maxs[2] )
{
	int s, t;

	GL_Bind( image );

	for ( t = mins[1]+HALF_SKY_SUBDIVISIONS; t < maxs[1]+HALF_SKY_SUBDIVISIONS; t++ )
	{
		qglBegin( GL_TRIANGLE_STRIP );

		for ( s = mins[0]+HALF_SKY_SUBDIVISIONS; s <= maxs[0]+HALF_SKY_SUBDIVISIONS; s++ )
		{
			qglTexCoord2fv( s_skyTexCoords[t][s] );
			qglVertex3fv( s_skyPoints[t][s] );

			qglTexCoord2fv( s_skyTexCoords[t+1][s] );
			qglVertex3fv( s_skyPoints[t+1][s] );
		}

		qglEnd();
	}
}
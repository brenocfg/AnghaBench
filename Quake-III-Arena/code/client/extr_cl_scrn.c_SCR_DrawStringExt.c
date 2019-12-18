#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  color ;
struct TYPE_2__ {int /*<<< orphan*/  (* SetColor ) (float*) ;} ;

/* Variables and functions */
 size_t ColorIndex (char const) ; 
 int /*<<< orphan*/  Com_Memcpy (float*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ Q_IsColorString (char const*) ; 
 int /*<<< orphan*/  SCR_DrawChar (int,int,float,char const) ; 
 int /*<<< orphan*/ * g_color_table ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (float*) ; 
 int /*<<< orphan*/  stub2 (float*) ; 
 int /*<<< orphan*/  stub3 (float*) ; 
 int /*<<< orphan*/  stub4 (float*) ; 

void SCR_DrawStringExt( int x, int y, float size, const char *string, float *setColor, qboolean forceColor ) {
	vec4_t		color;
	const char	*s;
	int			xx;

	// draw the drop shadow
	color[0] = color[1] = color[2] = 0;
	color[3] = setColor[3];
	re.SetColor( color );
	s = string;
	xx = x;
	while ( *s ) {
		if ( Q_IsColorString( s ) ) {
			s += 2;
			continue;
		}
		SCR_DrawChar( xx+2, y+2, size, *s );
		xx += size;
		s++;
	}


	// draw the colored text
	s = string;
	xx = x;
	re.SetColor( setColor );
	while ( *s ) {
		if ( Q_IsColorString( s ) ) {
			if ( !forceColor ) {
				Com_Memcpy( color, g_color_table[ColorIndex(*(s+1))], sizeof( color ) );
				color[3] = setColor[3];
				re.SetColor( color );
			}
			s += 2;
			continue;
		}
		SCR_DrawChar( xx, y, size, *s );
		xx += size;
		s++;
	}
	re.SetColor( NULL );
}
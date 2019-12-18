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
typedef  int /*<<< orphan*/ * vec4_t ;
typedef  int /*<<< orphan*/  tempcolor ;
struct TYPE_2__ {int scale; int bias; int /*<<< orphan*/  charset; } ;

/* Variables and functions */
 size_t ColorIndex (char const) ; 
 scalar_t__ Q_IsColorString (char const*) ; 
 int /*<<< orphan*/ * g_color_table ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qfalse ; 
 int /*<<< orphan*/  trap_R_DrawStretchPic (float,float,float,float,float,float,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_R_SetColor (int /*<<< orphan*/ *) ; 
 TYPE_1__ uis ; 

__attribute__((used)) static void UI_DrawString2( int x, int y, const char* str, vec4_t color, int charw, int charh )
{
	const char* s;
	char	ch;
	int forceColor = qfalse; //APSFIXME;
	vec4_t	tempcolor;
	float	ax;
	float	ay;
	float	aw;
	float	ah;
	float	frow;
	float	fcol;

	if (y < -charh)
		// offscreen
		return;

	// draw the colored text
	trap_R_SetColor( color );
	
	ax = x * uis.scale + uis.bias;
	ay = y * uis.scale;
	aw = charw * uis.scale;
	ah = charh * uis.scale;

	s = str;
	while ( *s )
	{
		if ( Q_IsColorString( s ) )
		{
			if ( !forceColor )
			{
				memcpy( tempcolor, g_color_table[ColorIndex(s[1])], sizeof( tempcolor ) );
				tempcolor[3] = color[3];
				trap_R_SetColor( tempcolor );
			}
			s += 2;
			continue;
		}

		ch = *s & 255;
		if (ch != ' ')
		{
			frow = (ch>>4)*0.0625;
			fcol = (ch&15)*0.0625;
			trap_R_DrawStretchPic( ax, ay, aw, ah, fcol, frow, fcol + 0.0625, frow + 0.0625, uis.charset );
		}

		ax += aw;
		s++;
	}

	trap_R_SetColor( NULL );
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int contents; int surf; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_5__ {int numsides; int contents; int /*<<< orphan*/  brushnum; int /*<<< orphan*/  entitynum; TYPE_1__* original_sides; } ;
typedef  TYPE_2__ mapbrush_t ;

/* Variables and functions */
 int CONTENTS_DONOTENTER ; 
 int CONTENTS_FOG ; 
 int CONTENTS_LADDER ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_STRUCTURAL ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  Log_Print (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Log_Write (char*,...) ; 
 int /*<<< orphan*/  PrintContents (int) ; 
 int SURF_HINT ; 
 int SURF_SKIP ; 

int	Q3_BrushContents(mapbrush_t *b)
{
	int contents, i, mixed, hint;
	side_t *s;

	s = &b->original_sides[0];
	contents = s->contents;
	//
	mixed = false;
	hint = false;
	for (i = 1; i < b->numsides; i++)
	{
		s = &b->original_sides[i];
		if (s->contents != contents) mixed = true;
		if (s->surf & (SURF_HINT|SURF_SKIP)) hint = true;
		contents |= s->contents;
	} //end for
	//
	if (hint)
	{
		if (contents)
		{
			Log_Write("WARNING: hint brush with contents: ");
			PrintContents(contents);
			Log_Write("\r\n");
			//
			Log_Write("brush contents is: ");
			PrintContents(b->contents);
			Log_Write("\r\n");
		} //end if
		return 0;
	} //end if
	//Log_Write("brush %d contents ", nummapbrushes);
	//PrintContents(contents);
	//Log_Write("\r\n");
	//remove ladder and fog contents
	contents &= ~(CONTENTS_LADDER|CONTENTS_FOG);
	//
	if (mixed)
	{
		Log_Write("Entity %i, Brush %i: mixed face contents "
			, b->entitynum, b->brushnum);
		PrintContents(contents);
		Log_Write("\r\n");
		//
		Log_Write("brush contents is: ");
		PrintContents(b->contents);
		Log_Write("\r\n");
		//
		if (contents & CONTENTS_DONOTENTER) return CONTENTS_DONOTENTER;//Log_Print("mixed contents with donotenter\n");
		/*
		Log_Print("contents:"); PrintContents(contents);
		Log_Print("\ncontents:"); PrintContents(s->contents);
		Log_Print("\n");
		Log_Print("texture name = %s\n", texinfo[s->texinfo].texture);
		*/
		//if liquid brush
		if (contents & (CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER))
		{
			return (contents & (CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER));
		} //end if
		if (contents & CONTENTS_PLAYERCLIP) return (contents & CONTENTS_PLAYERCLIP);
		return (contents & CONTENTS_SOLID);
	} //end if
	/*
	if (contents & CONTENTS_AREAPORTAL)
	{
		static int num;
		Log_Write("Entity %i, Brush %i: area portal %d\r\n", b->entitynum, b->brushnum, num++);
	} //end if*/
	if (contents == (contents & CONTENTS_STRUCTURAL))
	{
		//Log_Print("brush %i is only structural\n", b->brushnum);
		contents = 0;
	} //end if
	if (contents & CONTENTS_DONOTENTER)
	{
		Log_Print("brush %i is a donotenter brush, c = %X\n", b->brushnum, contents);
	} //end if
	return contents;
}
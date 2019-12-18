#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int contents; size_t texinfo; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_7__ {int numsides; int entitynum; int brushnum; TYPE_1__* original_sides; } ;
typedef  TYPE_2__ mapbrush_t ;
struct TYPE_9__ {int translucence; } ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int CONTENTS_DETAIL ; 
 int CONTENTS_DUMMYFENCE ; 
 int CONTENTS_FENCE ; 
 int CONTENTS_Q2TRANSLUCENT ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_WINDOW ; 
 int SURF_TRANS33 ; 
 int SURF_TRANS66 ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 TYPE_4__* sin_texinfo ; 
 TYPE_3__* texinfo ; 

int Sin_BrushContents(mapbrush_t *b)
{
	int			contents;
	side_t		*s;
	int			i;
#ifdef SIN
	float			trans = 0;
#else
	int			trans;
#endif

	s = &b->original_sides[0];
	contents = s->contents;

#ifdef SIN
	trans = sin_texinfo[s->texinfo].translucence;
#else
	trans = texinfo[s->texinfo].flags;
#endif
	for (i=1 ; i<b->numsides ; i++, s++)
	{
		s = &b->original_sides[i];
#ifdef SIN
		trans += sin_texinfo[s->texinfo].translucence;
#else
		trans |= texinfo[s->texinfo].flags;
#endif
		if (s->contents != contents)
		{
#ifdef SIN
      if ( 
            ( s->contents & CONTENTS_DETAIL && !(contents & CONTENTS_DETAIL) ) ||
            ( !(s->contents & CONTENTS_DETAIL) && contents & CONTENTS_DETAIL ) 
         )
         {
         s->contents |= CONTENTS_DETAIL;
         contents |= CONTENTS_DETAIL;
         continue;
         }
#endif
			printf ("Entity %i, Brush %i: mixed face contents\n"
				, b->entitynum, b->brushnum);
			break;
		}
	}


#ifdef SIN
	if (contents & CONTENTS_FENCE)
	{
//		contents |= CONTENTS_TRANSLUCENT;
		contents |= CONTENTS_DETAIL;
		contents |= CONTENTS_DUMMYFENCE;
		contents &= ~CONTENTS_SOLID;
		contents &= ~CONTENTS_FENCE;
		contents |= CONTENTS_WINDOW;
	}
#endif

	// if any side is translucent, mark the contents
	// and change solid to window
#ifdef SIN
	if ( trans > 0 )
#else
	if ( trans & (SURF_TRANS33|SURF_TRANS66) )
#endif
	{
		contents |= CONTENTS_Q2TRANSLUCENT;
		if (contents & CONTENTS_SOLID)
		{
			contents &= ~CONTENTS_SOLID;
			contents |= CONTENTS_WINDOW;
		}
	}

	return contents;
}
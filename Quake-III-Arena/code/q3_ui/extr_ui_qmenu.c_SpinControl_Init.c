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
struct TYPE_4__ {char const* name; int left; int x; int right; scalar_t__ y; scalar_t__ bottom; scalar_t__ top; } ;
struct TYPE_5__ {int numitems; char** itemnames; TYPE_1__ generic; } ;
typedef  TYPE_2__ menulist_s ;

/* Variables and functions */
 scalar_t__ SMALLCHAR_HEIGHT ; 
 int SMALLCHAR_WIDTH ; 
 int strlen (char const*) ; 

__attribute__((used)) static void SpinControl_Init( menulist_s *s ) {
	int	len;
	int	l;
	const char* str;

	if (s->generic.name)
		len = strlen(s->generic.name) * SMALLCHAR_WIDTH;
	else
		len = 0;

	s->generic.left	= s->generic.x - SMALLCHAR_WIDTH - len;

	len = s->numitems = 0;
	while ( (str = s->itemnames[s->numitems]) != 0 )
	{
		l = strlen(str);
		if (l > len)
			len = l;

		s->numitems++;
	}		

	s->generic.top	  =	s->generic.y;
	s->generic.right  =	s->generic.x + (len+1)*SMALLCHAR_WIDTH;
	s->generic.bottom =	s->generic.y + SMALLCHAR_HEIGHT;
}
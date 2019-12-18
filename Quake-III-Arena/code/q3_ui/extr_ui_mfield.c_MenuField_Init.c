#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; scalar_t__ y; scalar_t__ bottom; scalar_t__ x; scalar_t__ right; scalar_t__ top; scalar_t__ left; scalar_t__ name; } ;
struct TYPE_7__ {int widthInChars; } ;
struct TYPE_6__ {TYPE_1__ generic; TYPE_4__ field; } ;
typedef  TYPE_2__ menufield_s ;

/* Variables and functions */
 int BIGCHAR_HEIGHT ; 
 int BIGCHAR_WIDTH ; 
 int /*<<< orphan*/  MField_Clear (TYPE_4__*) ; 
 int QMF_SMALLFONT ; 
 int SMALLCHAR_HEIGHT ; 
 int SMALLCHAR_WIDTH ; 
 int strlen (scalar_t__) ; 

void MenuField_Init( menufield_s* m ) {
	int	l;
	int	w;
	int	h;

	MField_Clear( &m->field );

	if (m->generic.flags & QMF_SMALLFONT)
	{
		w = SMALLCHAR_WIDTH;
		h = SMALLCHAR_HEIGHT;
	}
	else
	{
		w = BIGCHAR_WIDTH;
		h = BIGCHAR_HEIGHT;
	}	

	if (m->generic.name) {
		l = (strlen( m->generic.name )+1) * w;		
	}
	else {
		l = 0;
	}

	m->generic.left   = m->generic.x - l;
	m->generic.top    = m->generic.y;
	m->generic.right  = m->generic.x + w + m->field.widthInChars*w;
	m->generic.bottom = m->generic.y + h;
}
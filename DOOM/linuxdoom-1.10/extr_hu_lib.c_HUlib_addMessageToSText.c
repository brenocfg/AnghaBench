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
struct TYPE_4__ {size_t cl; int /*<<< orphan*/ * l; } ;
typedef  TYPE_1__ hu_stext_t ;

/* Variables and functions */
 int /*<<< orphan*/  HUlib_addCharToTextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUlib_addLineToSText (TYPE_1__*) ; 

void
HUlib_addMessageToSText
( hu_stext_t*	s,
  char*		prefix,
  char*		msg )
{
    HUlib_addLineToSText(s);
    if (prefix)
	while (*prefix)
	    HUlib_addCharToTextLine(&s->l[s->cl], *(prefix++));

    while (*msg)
	HUlib_addCharToTextLine(&s->l[s->cl], *(msg++));
}
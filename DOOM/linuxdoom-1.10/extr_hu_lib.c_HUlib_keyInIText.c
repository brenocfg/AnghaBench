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
struct TYPE_4__ {int /*<<< orphan*/  l; } ;
typedef  TYPE_1__ hu_itext_t ;
typedef  int boolean ;

/* Variables and functions */
 int /*<<< orphan*/  HUlib_addCharToTextLine (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  HUlib_delCharFromIText (TYPE_1__*) ; 
 unsigned char KEY_BACKSPACE ; 
 unsigned char KEY_ENTER ; 

boolean
HUlib_keyInIText
( hu_itext_t*	it,
  unsigned char ch )
{

    if (ch >= ' ' && ch <= '_') 
  	HUlib_addCharToTextLine(&it->l, (char) ch);
    else 
	if (ch == KEY_BACKSPACE) 
	    HUlib_delCharFromIText(it);
	else 
	    if (ch != KEY_ENTER) 
		return false; // did not eat key

    return true; // ate the key

}
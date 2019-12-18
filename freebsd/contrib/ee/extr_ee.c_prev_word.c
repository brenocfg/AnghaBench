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

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  left (int /*<<< orphan*/ ) ; 
 char* point ; 
 int position ; 
 int /*<<< orphan*/  right (int /*<<< orphan*/ ) ; 

void 
prev_word()	/* move to start of previous word in text	*/
{
	if (position != 1)
	{
		if ((position != 1) && ((point[-1] == ' ') || (point[-1] == '\t')))
		{	/* if at the start of a word	*/
			while ((position != 1) && ((*point != ' ') && (*point != '\t')))
				left(TRUE);
		}
		while ((position != 1) && ((*point == ' ') || (*point == '\t')))
			left(TRUE);
		while ((position != 1) && ((*point != ' ') && (*point != '\t')))
			left(TRUE);
		if ((position != 1) && ((*point == ' ') || (*point == '\t')))
			right(TRUE);
	}
	else
		left(TRUE);
}
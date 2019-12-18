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
 char* column_separator () ; 
 char* next_col (char*,unsigned int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static unsigned
split_row(char *source, unsigned *offsets, unsigned *widths)
{
    int mark = (int) strlen(column_separator());
    char *next = 0;
    unsigned result = 0;
    unsigned offset = 0;

    do {
	if (result) {
	    offset = (unsigned) (mark + next - source);
	    widths[result - 1] = offset - offsets[result - 1] - (unsigned) mark;
	}
	offsets[result] = offset;
	++result;
    } while ((next = next_col(source, offset)) != 0);

    offset = (unsigned) strlen(source);
    widths[result - 1] = offset - offsets[result - 1];

    return result;
}
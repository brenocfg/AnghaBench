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
 int /*<<< orphan*/  cptr ; 
 int /*<<< orphan*/  get_line () ; 
 int next_inline () ; 

__attribute__((used)) static int
nextc(void)
{
    int ch;
    int finish = 0;

    do
    {
	switch (ch = next_inline())
	{
	case '\n':
	    get_line();
	    break;
	case ' ':
	case '\t':
	case '\f':
	case '\r':
	case '\v':
	case ',':
	case ';':
	    ++cptr;
	    break;
	case '\\':
	    ch = '%';
	    /* FALLTHRU */
	default:
	    finish = 1;
	    break;
	}
    }
    while (!finish);

    return ch;
}
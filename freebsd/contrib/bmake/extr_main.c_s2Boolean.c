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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

Boolean
s2Boolean(const char *s, Boolean bf)
{
    if (s) {
	switch(*s) {
	case '\0':			/* not set - the default wins */
	    break;
	case '0':
	case 'F':
	case 'f':
	case 'N':
	case 'n':
	    bf = FALSE;
	    break;
	case 'O':
	case 'o':
	    switch (s[1]) {
	    case 'F':
	    case 'f':
		bf = FALSE;
		break;
	    default:
		bf = TRUE;
		break;
	    }
	    break;
	default:
	    bf = TRUE;
	    break;
	}
    }
    return (bf);
}
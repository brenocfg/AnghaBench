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
typedef  int Boolean ;

/* Variables and functions */

Boolean
Dir_HasWildcards(char *name)
{
    char *cp;
    int wild = 0, brace = 0, bracket = 0;

    for (cp = name; *cp; cp++) {
	switch(*cp) {
	case '{':
		brace++;
		wild = 1;
		break;
	case '}':
		brace--;
		break;
	case '[':
		bracket++;
		wild = 1;
		break;
	case ']':
		bracket--;
		break;
	case '?':
	case '*':
		wild = 1;
		break;
	default:
		break;
	}
    }
    return wild && bracket == 0 && brace == 0;
}
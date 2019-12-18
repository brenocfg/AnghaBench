#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nameLen; char* name; } ;
struct TYPE_5__ {scalar_t__ len; char* ename; } ;
typedef  TYPE_1__ SuffixCmpData ;
typedef  TYPE_2__ Suff ;

/* Variables and functions */

__attribute__((used)) static char *
SuffSuffIsSuffix(const Suff *s, const SuffixCmpData *sd)
{
    char  *p1;	    	/* Pointer into suffix name */
    char  *p2;	    	/* Pointer into string being examined */

    if (sd->len < s->nameLen)
	return NULL;		/* this string is shorter than the suffix */

    p1 = s->name + s->nameLen;
    p2 = sd->ename;

    while (p1 >= s->name && *p1 == *p2) {
	p1--;
	p2--;
    }

    return (p1 == s->name - 1 ? p2 : NULL);
}
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
struct TYPE_4__ {int to; int from; } ;
typedef  TYPE_1__ substring_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_strlcpy (char*,TYPE_1__ const*,size_t) ; 

char *match_strdup(const substring_t *s)
{
	size_t sz = s->to - s->from + 1;
	char *p = kmalloc(sz, GFP_KERNEL);
	if (p)
		match_strlcpy(p, s, sz);
	return p;
}
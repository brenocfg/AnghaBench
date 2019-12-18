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
 int /*<<< orphan*/  advance (char**) ; 
 int stub1 (char const*,size_t,int,struct conf*,char const*) ; 

__attribute__((used)) static int
getvalue(const char *f, size_t l, bool local, void *r, char **p,
    int (*fun)(const char *, size_t, bool, struct conf *, const char *))
{
	char *ep = *p;

	advance(p);
	return (*fun)(f, l, local, r, ep);
}
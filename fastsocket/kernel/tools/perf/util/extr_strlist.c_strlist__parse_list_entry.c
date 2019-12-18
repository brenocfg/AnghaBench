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
struct strlist {int dummy; } ;

/* Variables and functions */
 int strlist__add (struct strlist*,char const*) ; 
 int strlist__load (struct strlist*,char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int strlist__parse_list_entry(struct strlist *self, const char *s)
{
	if (strncmp(s, "file://", 7) == 0)
		return strlist__load(self, s + 7);

	return strlist__add(self, s);
}
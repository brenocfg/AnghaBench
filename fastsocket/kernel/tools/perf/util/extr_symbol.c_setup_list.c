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
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 struct strlist* strlist__new (int,char const*) ; 

__attribute__((used)) static int setup_list(struct strlist **list, const char *list_str,
		      const char *list_name)
{
	if (list_str == NULL)
		return 0;

	*list = strlist__new(true, list_str);
	if (!*list) {
		pr_err("problems parsing %s list\n", list_name);
		return -1;
	}
	return 0;
}
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
struct event_filter {char* filter_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int append_filter_string(struct event_filter *filter,
				char *string)
{
	int newlen;
	char *new_filter_string;

	BUG_ON(!filter->filter_string);
	newlen = strlen(filter->filter_string) + strlen(string) + 1;
	new_filter_string = kmalloc(newlen, GFP_KERNEL);
	if (!new_filter_string)
		return -ENOMEM;

	strcpy(new_filter_string, filter->filter_string);
	strcat(new_filter_string, string);
	kfree(filter->filter_string);
	filter->filter_string = new_filter_string;

	return 0;
}
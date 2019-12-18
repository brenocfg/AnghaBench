#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct filter_arg {TYPE_1__ value; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */
 char* malloc_or_die (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *val_to_str(struct event_filter *filter, struct filter_arg *arg)
{
	char *str;

	str = malloc_or_die(30);

	snprintf(str, 30, "%lld", arg->value.val);

	return str;
}
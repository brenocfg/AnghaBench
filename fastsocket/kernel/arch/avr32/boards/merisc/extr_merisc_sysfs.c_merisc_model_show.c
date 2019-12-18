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
struct class {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 char* merisc_model () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static ssize_t merisc_model_show(struct class *class, char *buf)
{
	ssize_t ret = 0;

	sprintf(buf, "%s\n", merisc_model());
	ret = strlen(buf) + 1;

	return ret;
}
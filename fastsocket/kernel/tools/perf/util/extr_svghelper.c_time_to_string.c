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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static char *time_to_string(u64 duration)
{
	static char text[80];

	text[0] = 0;

	if (duration < 1000) /* less than 1 usec */
		return text;

	if (duration < 1000 * 1000) { /* less than 1 msec */
		sprintf(text, "%4.1f us", duration / 1000.0);
		return text;
	}
	sprintf(text, "%4.1f ms", duration / 1000.0 / 1000);

	return text;
}
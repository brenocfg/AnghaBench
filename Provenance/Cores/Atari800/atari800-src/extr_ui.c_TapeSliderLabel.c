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
 int CASSETTE_GetSize () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static void TapeSliderLabel(char *label, int value, void *user_data)
{
	if (value >= CASSETTE_GetSize())
		sprintf(label, "End");
	else
		snprintf(label, 10, "%i", value + 1);
}
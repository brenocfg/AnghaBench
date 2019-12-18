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
 char const** h_errlist ; 
 int h_nerr ; 

const char *
gai_strerror(int e)
{

	if (e < 0 || e >= h_nerr)
		return ("unknown error");
	return (h_errlist[e]);
}
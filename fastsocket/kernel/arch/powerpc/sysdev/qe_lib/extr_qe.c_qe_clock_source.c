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
typedef  enum qe_clock { ____Placeholder_qe_clock } qe_clock ;

/* Variables and functions */
 int QE_BRG1 ; 
 int QE_CLK1 ; 
 int QE_CLK_DUMMY ; 
 int QE_CLK_NONE ; 
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

enum qe_clock qe_clock_source(const char *source)
{
	unsigned int i;

	if (strcasecmp(source, "none") == 0)
		return QE_CLK_NONE;

	if (strncasecmp(source, "brg", 3) == 0) {
		i = simple_strtoul(source + 3, NULL, 10);
		if ((i >= 1) && (i <= 16))
			return (QE_BRG1 - 1) + i;
		else
			return QE_CLK_DUMMY;
	}

	if (strncasecmp(source, "clk", 3) == 0) {
		i = simple_strtoul(source + 3, NULL, 10);
		if ((i >= 1) && (i <= 24))
			return (QE_CLK1 - 1) + i;
		else
			return QE_CLK_DUMMY;
	}

	return QE_CLK_DUMMY;
}
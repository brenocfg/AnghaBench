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
struct s35390a {scalar_t__ twentyfourhour; } ;

/* Variables and functions */
 int bin2bcd (int) ; 

__attribute__((used)) static char s35390a_hr2reg(struct s35390a *s35390a, int hour)
{
	if (s35390a->twentyfourhour)
		return bin2bcd(hour);

	if (hour < 12)
		return bin2bcd(hour);

	return 0x40 | bin2bcd(hour - 12);
}
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
typedef  int /*<<< orphan*/  ieee754dp ;

/* Variables and functions */
 int /*<<< orphan*/  ieee754dp_1e31 () ; 
 int /*<<< orphan*/  ieee754dp_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754dp_fint (unsigned int) ; 

ieee754dp ieee754dp_funs(unsigned int u)
{
	if ((int) u < 0)
		return ieee754dp_add(ieee754dp_1e31(),
				     ieee754dp_fint(u & ~(1 << 31)));
	return ieee754dp_fint(u);
}
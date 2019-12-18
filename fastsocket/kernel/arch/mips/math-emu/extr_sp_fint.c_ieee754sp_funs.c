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
typedef  int /*<<< orphan*/  ieee754sp ;

/* Variables and functions */
 int /*<<< orphan*/  ieee754sp_1e31 () ; 
 int /*<<< orphan*/  ieee754sp_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754sp_fint (unsigned int) ; 

ieee754sp ieee754sp_funs(unsigned int u)
{
	if ((int) u < 0)
		return ieee754sp_add(ieee754sp_1e31(),
				     ieee754sp_fint(u & ~(1 << 31)));
	return ieee754sp_fint(u);
}
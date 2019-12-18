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
 scalar_t__ ieee754sp_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754sp_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee754sp_tint (int /*<<< orphan*/ ) ; 

unsigned int ieee754sp_tuns(ieee754sp x)
{
	ieee754sp hb = ieee754sp_1e31();

	/* what if x < 0 ?? */
	if (ieee754sp_lt(x, hb))
		return (unsigned) ieee754sp_tint(x);

	return (unsigned) ieee754sp_tint(ieee754sp_sub(x, hb)) |
	    ((unsigned) 1 << 31);
}
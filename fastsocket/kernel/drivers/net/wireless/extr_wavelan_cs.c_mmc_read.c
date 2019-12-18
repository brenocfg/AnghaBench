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
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ u_char ;

/* Variables and functions */
 scalar_t__ mmc_in (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mmc_read(u_long		base,
	 u_char		o,
	 u_char *	b,
	 int		n)
{
  o += n;
  b += n;

  while(n-- > 0)
    *(--b) = mmc_in(base, --o);
}
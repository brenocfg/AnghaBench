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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  modify_field (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
modify_general_field (char *addr, LONGEST fieldval, int bitpos, int bitsize)
{
  modify_field (addr + sizeof (LONGEST) * bitpos / (8 * sizeof (LONGEST)),
		fieldval, bitpos % (8 * sizeof (LONGEST)), bitsize);
}
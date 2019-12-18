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
struct rh_kabi_structs_6_2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 

void rh_kabi_6_2(struct rh_kabi_structs_6_2 *rh_kabi_structs_6_2)
{
	/* No one should ever call this function */
	panic("Problem exists between keyboard and your seat.");
}
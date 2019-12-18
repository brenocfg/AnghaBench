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
 int /*<<< orphan*/  fN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f_a ; 
 int /*<<< orphan*/  f_b ; 
 int /*<<< orphan*/  f_c ; 
 int /*<<< orphan*/  f_d ; 
 int /*<<< orphan*/  f_e ; 

int
main()
{
	fN(f_a, 1);
	fN(f_b, 2);
	fN(f_c, 3);
	fN(f_d, 4);
	fN(f_e, 5);
	fN(f_a, 11);
	fN(f_c, 13);
	fN(f_d, 14);
	fN(f_a, 101);
	fN(f_c, 103);
	fN(f_c, 1003);

	return (0);
}
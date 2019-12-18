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
 int /*<<< orphan*/  fN (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fN2 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  f_a ; 
 int /*<<< orphan*/  f_b ; 
 int /*<<< orphan*/  f_c ; 
 int /*<<< orphan*/  f_d ; 
 int /*<<< orphan*/  f_e ; 

int
main()
{
	/*
	 * Avoid length of 1, 2, 4, or 8 bytes so DTrace will treat the data as
	 * a byte array.
	 */
	char a[] = {(char)-7, (char)201, (char)0, (char)0, (char)28, (char)1};
	char b[] = {(char)84, (char)69, (char)0, (char)0, (char)28, (char)0};
	char c[] = {(char)84, (char)69, (char)0, (char)0, (char)28, (char)1};
	char d[] = {(char)-7, (char)201, (char)0, (char)0, (char)29, (char)0};
	char e[] = {(char)84, (char)69, (char)0, (char)0, (char)28, (char)0};

	fN(f_a, a, 1);
	fN(f_b, b, 0);
	fN(f_d, d, 102);
	fN2(f_e, e, -2);
	fN(f_c, c, 0);
	fN(f_a, a, -1);
	fN(f_d, d, 101);
	fN(f_e, e, -2);
	fN(f_e, e, 2);
	fN2(f_e, e, 2);

	return (0);
}
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
 int NSHORTOPTS ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int* optletter ; 
 int /*<<< orphan*/  setoptionbyindex (int,int) ; 

__attribute__((used)) static void
setoption(int flag, int val)
{
	int i;

	for (i = 0; i < NSHORTOPTS; i++)
		if (optletter[i] == flag) {
			setoptionbyindex(i, val);
			return;
		}
	error("Illegal option -%c", flag);
}
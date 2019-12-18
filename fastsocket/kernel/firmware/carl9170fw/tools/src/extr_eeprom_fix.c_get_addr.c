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
 int EINVAL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int get_val (char*,unsigned int*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int get_addr(char *str, unsigned int *val)
{
	int err;

	err = get_val(str, val);
	if (*val & 3) {
		fprintf(stderr, "Address 0x%.8x is not a multiple of 4.\n",
			*val);

		return -EINVAL;
	}

	return err;
}
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
 scalar_t__ calc_data_size ; 
 int /*<<< orphan*/  die (char*,int,int) ; 
 int do_read (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  input_fd ; 

__attribute__((used)) static int read_or_die(void *data, int size)
{
	int r;

	r = do_read(input_fd, data, size);
	if (r <= 0)
		die("reading input file (size expected=%d received=%d)",
		    size, r);

	if (calc_data_size)
		calc_data_size += r;

	return r;
}
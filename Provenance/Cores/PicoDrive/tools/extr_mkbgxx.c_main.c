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
 int /*<<< orphan*/  do_file (char*,char*) ; 

int main(int argc, char *argv[])
{
	if (argc != 3) return 1;

	do_file(argv[1], "bg40.bin");
	do_file(argv[2], "bg32.bin");

	return 0;
}
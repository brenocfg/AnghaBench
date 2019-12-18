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
 int djb2_hash (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 char* program ; 
 int r5_hash (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
	program = argv[0];

	if (argc != 3)
		usage();
	if (!strcmp(argv[1], "djb2"))
		printf("%d\n", djb2_hash(argv[2]));
	else if (!strcmp(argv[1], "r5"))
		printf("%d\n", r5_hash(argv[2]));
	else
		usage();
	exit(0);
}
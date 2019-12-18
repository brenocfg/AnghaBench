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
 int getopt (int,char**,char*) ; 
 char* prog ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 int x86_64 ; 

__attribute__((used)) static void parse_args(int argc, char **argv)
{
	int c;
	prog = argv[0];
	while ((c = getopt(argc, argv, "ynv")) != -1) {
		switch (c) {
		case 'y':
			x86_64 = 1;
			break;
		case 'n':
			x86_64 = 0;
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			usage();
		}
	}
}
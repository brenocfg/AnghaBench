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
 int e_flag ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  test_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_folder (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	int opt, flag;

	flag = 0;
	e_flag = 0;

	while ((opt = getopt(argc, argv, "ef:d:")) > 0) {
		switch (opt) {
			case 'f':
				test_file(optarg);
				flag = 1;
				break;
			case 'd':
				test_folder(optarg);
				flag = 1;
				break;
			case 'e':
				e_flag = 1;
				break;
			default:
				printf("Usage: %s [-e] [-f <file_name.cs>] [-d <directory>]\n", argv[0]);
				exit(-1);
		}
	}

	if (flag == 0) {
		printf("Usage: %s [-e] [-f <file_name.cs>] [-d <directory>]\n", argv[0]);
		exit(-1);
	}

	return 0;
}
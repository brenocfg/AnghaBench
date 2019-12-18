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
 int atoi (char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (int) ; 

int main(int argc, char *argv[])
{
	int i, n = 500000; // by default, output 5 million integers
	if (argc > 1) n = atoi(argv[1]);
	srand(11);
	for (i = 0; i < n; ++i)
		printf("%u\n", (unsigned)((rand() % (n/4))  * 271828183u)); // 4 times in average
	return 0;
}
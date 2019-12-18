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
 int EOF ; 
 int getchar () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char *argv[])
{
	int ch, total=0;

	if (argc > 1)
		printf("const char %s[] %s=\n",
			argv[1], argc > 2 ? argv[2] : "");

	do {
		printf("\t\"");
		while ((ch = getchar()) != EOF)
		{
			total++;
			printf("\\x%02x",ch);
			if (total % 16 == 0)
				break;
		}
		printf("\"\n");
	} while (ch != EOF);

	if (argc > 1)
		printf("\t;\n\nconst int %s_size = %d;\n", argv[1], total);

	return 0;
}
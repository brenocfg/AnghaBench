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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int* active ; 
 int activec ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_max () ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/ * ptr ; 
 int ptrc ; 
 int /*<<< orphan*/  search_active () ; 
 int /*<<< orphan*/  select_max () ; 
 int /*<<< orphan*/  srandom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int
main(int argc, char *argv[])
{
	int i, u, b, c;
	FILE *f;


	srandom(time(NULL));

	ptrc = argc - 1;

	/*
	 * read data
	 */

	for (i = 0; i < ptrc; i++)
	{
		ptr[i] = malloc(0x800);
		f = fopen(argv[i + 1], "rb");
		fread(ptr[i], 1, 0x800, f);
		fclose(f);
		active[i] = i;
	}
	activec = ptrc;

	while (activec > 0)
	{
		fill_max();
		select_max();
		search_active();
	}

	return 0;
}
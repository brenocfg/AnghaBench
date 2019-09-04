#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ptr_no_space ;
struct TYPE_3__ {char* word; int count; struct TYPE_3__* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HASHLEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int) ; 
 TYPE_1__** head ; 

void write_to_file()
{
	FILE *fp = fopen("result.txt", "w");
	assert(fp);

	int i = 0;
	while (i < HASHLEN)
	{
		for (ptr_no_space p = head[i]; p != NULL; p = p->next)
			fprintf(fp, "%s  %d\n", p->word, p->count);
		i++;
	}
	fclose(fp);
}
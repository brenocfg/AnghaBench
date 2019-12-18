#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct source_line {struct source_line* path; } ;
struct annotation {TYPE_1__* src; } ;
struct TYPE_2__ {struct source_line* lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct source_line*) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 

__attribute__((used)) static void symbol__free_source_line(struct symbol *sym, int len)
{
	struct annotation *notes = symbol__annotation(sym);
	struct source_line *src_line = notes->src->lines;
	int i;

	for (i = 0; i < len; i++)
		free(src_line[i].path);

	free(src_line);
	notes->src->lines = NULL;
}
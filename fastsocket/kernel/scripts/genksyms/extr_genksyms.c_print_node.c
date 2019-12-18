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
struct string_list {size_t tag; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t SYM_NORMAL ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 char** symbol_type_name ; 

__attribute__((used)) static void print_node(FILE * f, struct string_list *list)
{
	if (list->tag != SYM_NORMAL) {
		putc(symbol_type_name[list->tag][0], f);
		putc('#', f);
	}
	fputs(list->string, f);
}
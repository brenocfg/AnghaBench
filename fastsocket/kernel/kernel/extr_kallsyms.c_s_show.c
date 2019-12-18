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
struct seq_file {struct kallsym_iter* private; } ;
struct kallsym_iter {int /*<<< orphan*/ * name; int /*<<< orphan*/  type; scalar_t__ value; scalar_t__* module_name; scalar_t__ exported; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,void*,char,int /*<<< orphan*/ *,...) ; 
 char tolower (int /*<<< orphan*/ ) ; 
 char toupper (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s_show(struct seq_file *m, void *p)
{
	struct kallsym_iter *iter = m->private;

	/* Some debugging symbols have no name.  Ignore them. */
	if (!iter->name[0])
		return 0;

	if (iter->module_name[0]) {
		char type;

		/*
		 * Label it "global" if it is exported,
		 * "local" if not exported.
		 */
		type = iter->exported ? toupper(iter->type) :
					tolower(iter->type);
		seq_printf(m, "%pK %c %s\t[%s]\n", (void *)iter->value,
			   type, iter->name, iter->module_name);
	} else
		seq_printf(m, "%pK %c %s\n", (void *)iter->value,
			   iter->type, iter->name);
	return 0;
}
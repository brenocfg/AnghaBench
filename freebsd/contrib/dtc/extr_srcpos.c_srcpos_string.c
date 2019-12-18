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
struct srcpos {int /*<<< orphan*/  first_column; int /*<<< orphan*/  first_line; int /*<<< orphan*/  last_column; int /*<<< orphan*/  last_line; TYPE_1__* file; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  xasprintf (char**,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

char *
srcpos_string(struct srcpos *pos)
{
	const char *fname = "<no-file>";
	char *pos_str;

	if (pos->file && pos->file->name)
		fname = pos->file->name;


	if (pos->first_line != pos->last_line)
		xasprintf(&pos_str, "%s:%d.%d-%d.%d", fname,
			  pos->first_line, pos->first_column,
			  pos->last_line, pos->last_column);
	else if (pos->first_column != pos->last_column)
		xasprintf(&pos_str, "%s:%d.%d-%d", fname,
			  pos->first_line, pos->first_column,
			  pos->last_column);
	else
		xasprintf(&pos_str, "%s:%d.%d", fname,
			  pos->first_line, pos->first_column);

	return pos_str;
}
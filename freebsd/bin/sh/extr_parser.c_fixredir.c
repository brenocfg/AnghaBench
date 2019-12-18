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
struct TYPE_2__ {int dupfd; int /*<<< orphan*/ * vname; } ;
union node {TYPE_1__ ndup; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int digit_val (char const) ; 
 scalar_t__ is_digit (char const) ; 
 int /*<<< orphan*/ * makename () ; 
 int /*<<< orphan*/  synerror (char*) ; 

void
fixredir(union node *n, const char *text, int err)
{
	TRACE(("Fix redir %s %d\n", text, err));
	if (!err)
		n->ndup.vname = NULL;

	if (is_digit(text[0]) && text[1] == '\0')
		n->ndup.dupfd = digit_val(text[0]);
	else if (text[0] == '-' && text[1] == '\0')
		n->ndup.dupfd = -1;
	else {

		if (err)
			synerror("Bad fd number");
		else
			n->ndup.vname = makename();
	}
}
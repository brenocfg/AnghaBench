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
struct TYPE_3__ {int wide; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 int MARGIN ; 
 int MIN (int,int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,char*,int,char const*) ; 

__attribute__((used)) static void
print_line(MY_OBJ * obj, const char *line, int row)
{
    int width = obj->wide - (2 * MARGIN);
    int limit = MIN((int) strlen(line), width - 2);

    (void) wmove(obj->text, row, 0);	/* move cursor to correct line */
    wprintw(obj->text, " %.*s", limit, line);
    wclrtoeol(obj->text);
}
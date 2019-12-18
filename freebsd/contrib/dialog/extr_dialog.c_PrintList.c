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
struct TYPE_2__ {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 TYPE_1__ dialog_state ; 
 char const* dialog_version () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char const* const,char const*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 char* program ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
PrintList(const char *const *list)
{
    const char *leaf = strrchr(program, '/');
    unsigned n = 0;

    if (leaf != 0)
	leaf++;
    else
	leaf = program;

    while (*list != 0) {
	fprintf(dialog_state.output, *list, n ? leaf : dialog_version());
	(void) fputc('\n', dialog_state.output);
	n = 1;
	list++;
    }
}
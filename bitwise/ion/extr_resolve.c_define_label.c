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
struct TYPE_3__ {int defined; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_1__ Label ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__* get_label (int /*<<< orphan*/ ,char const*) ; 

void define_label(SrcPos pos, const char *name) {
    Label *label = get_label(pos, name);
    if (label->defined) {
        fatal_error(pos, "Multiple definitions of label '%s'", name);
    }
    label->defined = true;
}
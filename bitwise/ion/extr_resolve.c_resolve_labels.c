#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  pos; scalar_t__ referenced; scalar_t__ defined; } ;
typedef  TYPE_1__ Label ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* labels ; 
 TYPE_1__* labels_end ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void resolve_labels(void) {
    for (Label *label = labels; label != labels_end; label++) {
        if (label->referenced && !label->defined) {
            fatal_error(label->pos, "Label '%s' referenced but not defined", label->name);
        }
        if (label->defined && !label->referenced) {
            warning(label->pos, "Label '%s' defined but not referenced", label->name);
        }
    }
    labels_end = labels;
}
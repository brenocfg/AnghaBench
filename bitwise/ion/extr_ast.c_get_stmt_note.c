#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* name; } ;
struct TYPE_6__ {size_t num_notes; TYPE_3__* notes; } ;
struct TYPE_7__ {TYPE_1__ notes; } ;
typedef  TYPE_2__ Stmt ;
typedef  TYPE_3__ Note ;

/* Variables and functions */

Note *get_stmt_note(Stmt *stmt, const char *name) {
    for (size_t i = 0; i < stmt->notes.num_notes; i++) {
        Note *note = stmt->notes.notes + i;
        if (note->name == name) {
            return note;
        }
    }
    return NULL;
}
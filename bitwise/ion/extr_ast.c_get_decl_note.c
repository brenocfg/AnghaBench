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
struct TYPE_6__ {size_t num_notes; TYPE_2__* notes; } ;
struct TYPE_8__ {TYPE_1__ notes; } ;
struct TYPE_7__ {char const* name; } ;
typedef  TYPE_2__ Note ;
typedef  TYPE_3__ Decl ;

/* Variables and functions */

Note *get_decl_note(Decl *decl, const char *name) {
    if (!decl) {
        return NULL;
    }
    for (size_t i = 0; i < decl->notes.num_notes; i++) {
        Note *note = decl->notes.notes + i;
        if (note->name == name) {
            return note;
        }
    }
    return NULL;
}
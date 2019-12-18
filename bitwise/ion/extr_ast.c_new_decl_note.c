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
struct TYPE_4__ {int /*<<< orphan*/  note; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Note ;
typedef  TYPE_1__ Decl ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_NOTE ; 
 TYPE_1__* new_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Decl *new_decl_note(SrcPos pos, Note note) {
    Decl *d = new_decl(DECL_NOTE, pos, NULL);
    d->note = note;
    return d;
}
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
struct TYPE_4__ {struct TYPE_4__* text; struct TYPE_4__* effect; struct TYPE_4__* name; struct TYPE_4__* style; } ;
typedef  TYPE_1__ ASSDialog ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

void ff_ass_free_dialog(ASSDialog **dialogp)
{
    ASSDialog *dialog = *dialogp;
    if (!dialog)
        return;
    av_freep(&dialog->style);
    av_freep(&dialog->name);
    av_freep(&dialog->effect);
    av_freep(&dialog->text);
    av_freep(dialogp);
}
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
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  cursor; } ;
typedef  TYPE_1__ YuiScsp ;

/* Variables and functions */
 int /*<<< orphan*/  ScspSlotDebugStats (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_strstrip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_text_buffer_set_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  yui_scsp_clear (TYPE_1__*) ; 

void yui_scsp_fill(YuiScsp * scsp) {
	gchar nameTemp[1024];

	yui_scsp_clear(scsp);

	ScspSlotDebugStats(scsp->cursor, nameTemp );

	gtk_text_buffer_set_text(scsp->buffer, g_strstrip(nameTemp), -1);
}
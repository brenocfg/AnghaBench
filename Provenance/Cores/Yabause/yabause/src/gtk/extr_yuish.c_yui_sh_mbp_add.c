#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gpointer ;
typedef  scalar_t__ gchar ;
struct TYPE_5__ {int /*<<< orphan*/  debugsh; } ;
typedef  TYPE_1__ YuiSh ;
typedef  int /*<<< orphan*/  GtkEntry ;

/* Variables and functions */
 int BREAK_BYTEREAD ; 
 int BREAK_BYTEWRITE ; 
 int BREAK_LONGREAD ; 
 int BREAK_LONGWRITE ; 
 int BREAK_WORDREAD ; 
 int BREAK_WORDWRITE ; 
 int /*<<< orphan*/  SH2AddMemoryBreakpoint (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  SH2UpdateMemoryBreakpointList (TYPE_1__*) ; 
 scalar_t__* gtk_entry_get_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sscanf (scalar_t__ const*,char*,unsigned int*) ; 

__attribute__((used)) static void yui_sh_mbp_add(GtkEntry * entry, gpointer user_data) {
	YuiSh * sh2 = user_data;
	const gchar * address_s;
	unsigned int address;

	address_s = gtk_entry_get_text(entry);

	if (*address_s == 0) return;

	sscanf(address_s, "%8X", &address);

	SH2AddMemoryBreakpoint(sh2->debugsh, address, BREAK_BYTEREAD|BREAK_WORDREAD|BREAK_LONGREAD|BREAK_BYTEWRITE|BREAK_WORDWRITE|BREAK_LONGWRITE);

	gtk_entry_set_text(entry, "");

	SH2UpdateMemoryBreakpointList(sh2);
}
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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ gpointer ;
typedef  scalar_t__ gboolean ;
struct TYPE_2__ {scalar_t__ (* Scan ) (int) ;int /*<<< orphan*/  (* KeyName ) (scalar_t__,char*,int) ;int /*<<< orphan*/  Name; int /*<<< orphan*/  canScan; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_1__* PERCore ; 
 int PERSF_BUTTON ; 
 int PERSF_HAT ; 
 int PERSF_KEY ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  entry_hack ; 
 int /*<<< orphan*/  g_key_file_set_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_watching ; 
 int /*<<< orphan*/  keyfile ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ stub1 (int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,char*,int) ; 

__attribute__((used)) static gboolean watch_joy(gpointer name) {
	u32 i;

	if (! is_watching) return TRUE;

	if (! PERCore->canScan) {
		is_watching = FALSE;
		return TRUE;
	}

	i = PERCore->Scan(PERSF_KEY | PERSF_BUTTON | PERSF_HAT);

	if (i == 0) {
		return TRUE;
	} else {
		char tmp[100];

		sprintf(tmp, "Pad.%s.1", (char *)name); // should be group.name
		g_key_file_set_integer(keyfile, PERCore->Name, tmp, i);
		PERCore->KeyName(i, tmp, 100);
		gtk_entry_set_text(entry_hack, tmp);
		is_watching = FALSE;
		return FALSE;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_5__ {int addr; } ;
typedef  TYPE_1__ codebreakpoint_struct ;
struct TYPE_6__ {int /*<<< orphan*/  bpListStore; int /*<<< orphan*/  debugsh; } ;
typedef  TYPE_2__ YuiSh ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int MAX_BREAKPOINTS ; 
 TYPE_1__* SH2GetBreakpointList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 

void SH2UpdateBreakpointList(YuiSh * sh2) {
  const codebreakpoint_struct *cbp;
  int i;

  gtk_list_store_clear(GTK_LIST_STORE( sh2->bpListStore ));
  
  cbp = SH2GetBreakpointList(sh2->debugsh);
  
  for (i = 0; i < MAX_BREAKPOINTS-1; i++) {
    
    if (cbp[i].addr != 0xFFFFFFFF) {
      gchar tempstr[20];
      GtkTreeIter iter;
      gtk_list_store_append( GTK_LIST_STORE( sh2->bpListStore ), &iter );
      
      sprintf(tempstr, "%08X", (int)cbp[i].addr);
      gtk_list_store_set( GTK_LIST_STORE( sh2->bpListStore ), &iter, 0, tempstr, -1 );
    }
  } 
}
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
typedef  scalar_t__ u32 ;
typedef  char gchar ;
struct TYPE_4__ {int /*<<< orphan*/  regListStore; } ;
typedef  TYPE_1__ YuiSh ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRendererText ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter_from_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sh2setRegister (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_window_invalidate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_sh_editedReg( GtkCellRendererText *cellrenderertext,
			      gchar *arg1,
			      gchar *arg2,
			      YuiSh *sh2) {
  /* registry number <arg1> value has been set to <arg2> */

  GtkTreeIter iter;
  char bptext[10];
  char *endptr;
  int i = atoi(arg1);
  u32 addr;

  gtk_tree_model_get_iter_from_string( GTK_TREE_MODEL( sh2->regListStore ), &iter, arg1 );
  addr = strtoul(arg2, &endptr, 16 );
  if ( endptr - arg2 == strlen(arg2) ) {
   
    sprintf(bptext, "%08X", (int)addr);
    sh2setRegister( sh2, i, addr );
    gtk_list_store_set( GTK_LIST_STORE( sh2->regListStore ), &iter, 1, bptext, -1 );
  }
  yui_window_invalidate( yui );
}
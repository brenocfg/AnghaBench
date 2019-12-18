#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  PC; } ;
typedef  TYPE_1__ sh2regs_struct ;
typedef  char gchar ;
struct TYPE_8__ {int /*<<< orphan*/  debugsh; int /*<<< orphan*/  bpListStore; } ;
typedef  TYPE_2__ YuiSh ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRendererText ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2AddCodeBreakpoint (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SH2DelCodeBreakpoint (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SH2GetRegisters (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SH2UpdateBreakpointList (TYPE_2__*) ; 
 int /*<<< orphan*/  SH2UpdateCodeList (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter_from_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned int*) ; 
 int strlen (char*) ; 
 unsigned int strtoul (char*,char**,int) ; 

__attribute__((used)) static void yui_sh_editedBp( GtkCellRendererText *cellrenderertext,
			     gchar *arg1,
			     gchar *arg2,
			     YuiSh *sh2) {
  /* breakpoint <arg1> has been set to address <arg2> */

  GtkTreeIter iter;
  char *endptr;
  unsigned int addr;
  gchar * oldaddr_s;
  unsigned int oldaddr;

  gtk_tree_model_get_iter_from_string( GTK_TREE_MODEL( sh2->bpListStore ), &iter, arg1 );

  gtk_tree_model_get(GTK_TREE_MODEL( sh2->bpListStore ), &iter, 0, &oldaddr_s, -1);
  sscanf(oldaddr_s, "%8X", &oldaddr);
  g_free(oldaddr_s);

  SH2DelCodeBreakpoint(sh2->debugsh, oldaddr);

  addr = strtoul(arg2, &endptr, 16 );
  if ((endptr - arg2 < strlen(arg2)) || (!addr)) addr = 0xFFFFFFFF;

  if (addr != 0xFFFFFFFF) {
    SH2AddCodeBreakpoint(sh2->debugsh, addr);
  }

  {
    sh2regs_struct sh2regs;
    SH2GetRegisters(sh2->debugsh, &sh2regs);
    SH2UpdateCodeList(sh2,sh2regs.PC);
    SH2UpdateBreakpointList(sh2);
  }
}
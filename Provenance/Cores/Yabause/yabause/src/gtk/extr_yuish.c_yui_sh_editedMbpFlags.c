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
typedef  int /*<<< orphan*/  u32 ;
typedef  int gchar ;
struct TYPE_4__ {int /*<<< orphan*/  debugsh; int /*<<< orphan*/  mbpListStore; } ;
typedef  TYPE_1__ YuiSh ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRendererText ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_BYTEREAD ; 
 int /*<<< orphan*/  BREAK_BYTEWRITE ; 
 int /*<<< orphan*/  BREAK_LONGREAD ; 
 int /*<<< orphan*/  BREAK_LONGWRITE ; 
 int /*<<< orphan*/  BREAK_WORDREAD ; 
 int /*<<< orphan*/  BREAK_WORDWRITE ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2AddMemoryBreakpoint (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2DelMemoryBreakpoint (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SH2UpdateMemoryBreakpointList (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (int*) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int**,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter_from_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sscanf (int*,char*,unsigned int*) ; 

__attribute__((used)) static void yui_sh_editedMbpFlags( GtkCellRendererText *cellrenderertext,
			     gchar *arg1,
			     gchar *arg2,
			      YuiSh *sh2) {
  /* breakpoint <arg1> has been set to address <arg2> */
  
  GtkTreeIter iter;
  gchar *endptr;
  unsigned int addr;
  gchar * addr_s;
  u32 flags = 0;

  gtk_tree_model_get_iter_from_string( GTK_TREE_MODEL( sh2->mbpListStore ), &iter, arg1 );

  gtk_tree_model_get(GTK_TREE_MODEL( sh2->mbpListStore ), &iter, 0, &addr_s, -1);
  sscanf(addr_s, "%8X", &addr);
  g_free(addr_s);

  SH2DelMemoryBreakpoint(sh2->debugsh, addr);

  endptr = arg2;
    
  while ( *endptr ) {
      
    switch (*endptr) {
	
      case 'b': flags |= BREAK_BYTEREAD; break;
      case 'w': flags |= BREAK_WORDREAD; break;
      case 'l': flags |= BREAK_LONGREAD; break;
      case 'B': flags |= BREAK_BYTEWRITE; break;
      case 'W': flags |= BREAK_WORDWRITE; break;
      case 'L': flags |= BREAK_LONGWRITE; break;
      }
      endptr++;
  }
    
  SH2AddMemoryBreakpoint(sh2->debugsh, addr, flags);

  SH2UpdateMemoryBreakpointList(sh2);
}
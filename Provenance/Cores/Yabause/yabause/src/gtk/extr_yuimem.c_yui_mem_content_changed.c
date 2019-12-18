#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int gint ;
typedef  scalar_t__ gchar ;
struct TYPE_3__ {int wLine; int /*<<< orphan*/  yui; int /*<<< orphan*/  store; scalar_t__ address; } ;
typedef  TYPE_1__ YuiMem ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRendererText ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MappedMemoryWriteByte (int /*<<< orphan*/ ,int) ; 
 int atoi (scalar_t__*) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter_from_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int hexaDigitToInt (scalar_t__) ; 
 int /*<<< orphan*/  yui_window_invalidate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_mem_content_changed( GtkCellRendererText *cellrenderertext,
		      gchar *arg1,
		      gchar *arg2,
		      YuiMem *ym) {
  /* dump line <arg1> has been modified - new content is <arg2> */

  GtkTreeIter iter;
  gint i = atoi(arg1);
  gint j,k;
  gchar *curs;
  u32 addr = ym->address + i*ym->wLine;

  gtk_tree_model_get_iter_from_string( GTK_TREE_MODEL( ym->store ), &iter, arg1 );
  
  /* check the format : wLine*2 hexa digits */
  for ( curs = arg2, j=0 ; *curs ; curs++ )
    if ( hexaDigitToInt( *curs ) != -1 ) j++;

  if ( j != ym->wLine * 2 ) return;

  /* convert */
  for ( curs = arg2, k=-1 ; *curs ; curs++ ) { 

    if ( hexaDigitToInt( *curs )!=-1 ) {

      if ( k==-1 ) k = hexaDigitToInt( *curs );
      else { MappedMemoryWriteByte( addr++, 16*k + hexaDigitToInt( *curs ) ); k = -1;
      }
    }
  }
  yui_window_invalidate(ym->yui);
}
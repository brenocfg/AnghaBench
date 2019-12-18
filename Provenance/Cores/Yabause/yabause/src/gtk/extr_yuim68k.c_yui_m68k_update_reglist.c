#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ PC; scalar_t__ SR; scalar_t__* A; scalar_t__* D; } ;
typedef  TYPE_1__ m68kregs_struct ;
typedef  int /*<<< orphan*/  YuiM68k ;
struct TYPE_5__ {int /*<<< orphan*/  regListStore; } ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter_first (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_iter_next (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_3__* yui_m68k ; 

__attribute__((used)) static void yui_m68k_update_reglist( YuiM68k *m68k, m68kregs_struct *regs) {
  /* refresh the registery list */

  GtkTreeIter iter;
  char regstr[32];
  char valuestr[32];
  int i;
  
  for ( i = 0 ; i < 8 ; i++ ) {
    
    if ( i==0 ) gtk_tree_model_get_iter_first( GTK_TREE_MODEL( yui_m68k->regListStore ), &iter );
    else gtk_tree_model_iter_next( GTK_TREE_MODEL( yui_m68k->regListStore ), &iter );
    sprintf(regstr, "D%d", i );
    sprintf(valuestr, "%08x", (int)regs->D[i]);
    gtk_list_store_set( GTK_LIST_STORE( yui_m68k->regListStore ), &iter, 0, regstr, 1, valuestr, -1 );
  }
  for ( i = 0 ; i < 8 ; i++ ) {
    
    gtk_tree_model_iter_next( GTK_TREE_MODEL( yui_m68k->regListStore ), &iter );
    sprintf(regstr, "A%d", i );
    sprintf(valuestr, "%08x", (int)regs->A[i]);
    gtk_list_store_set( GTK_LIST_STORE( yui_m68k->regListStore ), &iter, 0, regstr, 1, valuestr, -1 );
  }

  gtk_tree_model_iter_next( GTK_TREE_MODEL( yui_m68k->regListStore ), &iter );
  sprintf(valuestr, "%08x", (int)regs->SR);
  gtk_list_store_set( GTK_LIST_STORE( yui_m68k->regListStore ), &iter, 0, "SR", 1, valuestr, -1 );

  gtk_tree_model_iter_next( GTK_TREE_MODEL( yui_m68k->regListStore ), &iter );
  sprintf(valuestr, "%08x", (int)regs->PC);
  gtk_list_store_set( GTK_LIST_STORE( yui_m68k->regListStore ), &iter, 0, "PC", 1, valuestr, -1 );
}
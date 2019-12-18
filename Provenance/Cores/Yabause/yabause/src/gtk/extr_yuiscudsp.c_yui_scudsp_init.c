#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {struct TYPE_16__* bpListRenderer; struct TYPE_16__* bpList; struct TYPE_16__* hboxmain; void* bpListColumn; void* bpListStore; struct TYPE_16__* regListRenderer2; struct TYPE_16__* regList; void* regListColumn2; void* regListColumn1; struct TYPE_16__* regListRenderer1; void* regListStore; struct TYPE_16__* uLabel; struct TYPE_16__* uFrame; struct TYPE_16__* vboxmain; struct TYPE_16__* hbox; struct TYPE_16__* vbox; } ;
typedef  TYPE_1__ YuiScudsp ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_CELL_RENDERER_MODE_EDITABLE ; 
 int /*<<< orphan*/  GTK_CONTAINER (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (void*) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW (TYPE_1__*) ; 
 int /*<<< orphan*/  G_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* gtk_frame_new (char*) ; 
 TYPE_1__* gtk_hbox_new (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* gtk_hbutton_box_new () ; 
 TYPE_1__* gtk_label_new (int /*<<< orphan*/ *) ; 
 void* gtk_list_store_new (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gtk_tree_view_append_column (int /*<<< orphan*/ ,void*) ; 
 void* gtk_tree_view_column_new_with_attributes (char*,TYPE_1__*,char*,int,int /*<<< orphan*/ *) ; 
 void* gtk_tree_view_new_with_model (int /*<<< orphan*/ ) ; 
 void* gtk_vbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_window_set_resizable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yui_scudsp_destroy ; 
 int /*<<< orphan*/  yui_scudsp_editedBp ; 
 int /*<<< orphan*/  yui_scudsp_editedReg ; 

__attribute__((used)) static void yui_scudsp_init (YuiScudsp * scudsp) {
  gtk_window_set_title(GTK_WINDOW(scudsp), "SCU-DSP");
  gtk_window_set_resizable( GTK_WINDOW(scudsp), FALSE );

  scudsp->vbox = gtk_vbox_new(FALSE, 2);
  gtk_container_set_border_width( GTK_CONTAINER( scudsp->vbox ),4 );
  gtk_container_add (GTK_CONTAINER (scudsp), scudsp->vbox);  

  scudsp->hboxmain = gtk_hbox_new(FALSE, 2);
  gtk_container_set_border_width( GTK_CONTAINER( scudsp->hboxmain ),4 );
  gtk_box_pack_start( GTK_BOX( scudsp->vbox ), scudsp->hboxmain, FALSE, FALSE, 4 );

  scudsp->hbox = gtk_hbutton_box_new();
  gtk_container_set_border_width( GTK_CONTAINER( scudsp->hbox ),4 );
  gtk_box_pack_start( GTK_BOX( scudsp->vbox ), scudsp->hbox, FALSE, FALSE, 4 ); 

  scudsp->vboxmain = gtk_vbox_new(FALSE, 2);
  gtk_container_set_border_width( GTK_CONTAINER( scudsp->vboxmain ),4 );
  gtk_box_pack_start( GTK_BOX( scudsp->hboxmain ), scudsp->vboxmain, FALSE, FALSE, 4 );

  /* unassembler frame */

  scudsp->uFrame = gtk_frame_new("Disassembled code");
  gtk_box_pack_start( GTK_BOX( scudsp->vboxmain ), scudsp->uFrame, FALSE, FALSE, 4 );
  
  scudsp->uLabel = gtk_label_new(NULL);
  gtk_container_add (GTK_CONTAINER (scudsp->uFrame), scudsp->uLabel );

  /* Register list */

  scudsp->regListStore = gtk_list_store_new(2,G_TYPE_STRING,G_TYPE_STRING);
  scudsp->regList = gtk_tree_view_new_with_model( GTK_TREE_MODEL(scudsp->regListStore) );
  scudsp->regListRenderer1 = gtk_cell_renderer_text_new();
  scudsp->regListRenderer2 = gtk_cell_renderer_text_new();
  g_object_set(G_OBJECT(scudsp->regListRenderer2), "editable", TRUE, "mode", GTK_CELL_RENDERER_MODE_EDITABLE, NULL );
  scudsp->regListColumn1 = gtk_tree_view_column_new_with_attributes("Register", scudsp->regListRenderer1, "text", 0, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(scudsp->regList), scudsp->regListColumn1);
  scudsp->regListColumn2 = gtk_tree_view_column_new_with_attributes("Value", scudsp->regListRenderer2, "text", 1, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(scudsp->regList), scudsp->regListColumn2);
  gtk_box_pack_start( GTK_BOX( scudsp->hboxmain ), scudsp->regList, FALSE, FALSE, 4 );
  g_signal_connect(G_OBJECT(scudsp->regListRenderer2), "edited", GTK_SIGNAL_FUNC(yui_scudsp_editedReg), scudsp );

  /* breakpoint list */

  scudsp->bpListStore = gtk_list_store_new(1,G_TYPE_STRING);
  scudsp->bpList = gtk_tree_view_new_with_model( GTK_TREE_MODEL(scudsp->bpListStore) );
  scudsp->bpListRenderer = gtk_cell_renderer_text_new();
  g_object_set(G_OBJECT(scudsp->bpListRenderer), "editable", TRUE, "mode", GTK_CELL_RENDERER_MODE_EDITABLE, NULL );
  scudsp->bpListColumn = gtk_tree_view_column_new_with_attributes("Breakpoints", scudsp->bpListRenderer, "text", 0, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(scudsp->bpList), scudsp->bpListColumn);
  gtk_box_pack_start( GTK_BOX( scudsp->hboxmain ), scudsp->bpList, FALSE, FALSE, 4 );
  g_signal_connect(G_OBJECT(scudsp->bpListRenderer), "edited", GTK_SIGNAL_FUNC(yui_scudsp_editedBp), scudsp );

  g_signal_connect(G_OBJECT(scudsp), "delete-event", GTK_SIGNAL_FUNC(yui_scudsp_destroy), NULL);
}
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
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * vbox; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeStore ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  CDCoreList ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDK_WINDOW_TYPE_HINT_DIALOG ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CAN_DEFAULT ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 TYPE_1__* GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_NOTEBOOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_POLICY_AUTOMATIC ; 
 int /*<<< orphan*/  GTK_POLICY_NEVER ; 
 int /*<<< orphan*/  GTK_RANGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_RESPONSE_CANCEL ; 
 int /*<<< orphan*/  GTK_RESPONSE_OK ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TOGGLE_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WIDGET_SET_FLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
 int /*<<< orphan*/  M68KCoreList ; 
 int /*<<< orphan*/  OSDCoreList ; 
 int /*<<< orphan*/  PERCoreList ; 
#define  PERMOUSE 129 
#define  PERPAD 128 
 int /*<<< orphan*/  SH2CoreList ; 
 int /*<<< orphan*/  SNDCoreList ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VIDCoreList ; 
 int /*<<< orphan*/  YUI_CHECK_BUTTON (int /*<<< orphan*/ *) ; 
 int YUI_FILE_ENTRY_BROWSE ; 
 int YUI_FILE_ENTRY_DIRECTORY ; 
 int /*<<< orphan*/  YUI_PAGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  YUI_RANGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bilinear_toggled ; 
 int /*<<< orphan*/  carttypes ; 
 int /*<<< orphan*/  cdcores ; 
 int /*<<< orphan*/  cores_to_range (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_enable_audio_sync ; 
 int /*<<< orphan*/  disable_enable_fixed_base_time ; 
 int /*<<< orphan*/  frameskip_toggled ; 
 int g_key_file_get_integer (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_from_stock (char*) ; 
 int /*<<< orphan*/ * gtk_cell_renderer_text_new () ; 
 int /*<<< orphan*/ * gtk_check_button_new_with_label (char*) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_dialog_add_action_widget (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_dialog_new () ; 
 int /*<<< orphan*/ * gtk_hbox_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_hscale_new_with_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gtk_label_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_notebook_append_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_notebook_new () ; 
 int /*<<< orphan*/  gtk_range_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_toggle_button_set_active (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_string (char*) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_store_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gtk_tree_view_append_column (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_column_new_with_attributes (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_expand_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_tree_view_new_with_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_set_headers_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_window_set_icon_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_window_set_resizable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_window_set_type_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hide_show_cart_path ; 
 int /*<<< orphan*/  hide_show_netlink ; 
 int /*<<< orphan*/  keyfile ; 
 int /*<<< orphan*/  m68kinterpreters ; 
 int /*<<< orphan*/  osdcores ; 
 int /*<<< orphan*/  percores ; 
 int /*<<< orphan*/  pertype_changed ; 
 int /*<<< orphan*/  regions ; 
 int /*<<< orphan*/  sh2interpreters ; 
 int /*<<< orphan*/  sndcores ; 
 int /*<<< orphan*/  vidcores ; 
 int /*<<< orphan*/  vidformats ; 
 int /*<<< orphan*/  volume_changed ; 
 int /*<<< orphan*/  yui_check_button_get_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yui_check_button_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * yui_file_entry_new (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int /*<<< orphan*/ * yui_page_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yui_page_new (int /*<<< orphan*/ ) ; 
 int yui_range_get_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yui_range_new (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yui_resolution_new (int /*<<< orphan*/ ,char*) ; 

GtkWidget* create_dialog1(void) {
  GtkWidget *dialog1;
  GtkWidget *notebook1;
  GtkWidget *vbox17;
  GtkWidget *hbox22;
  GtkWidget *button11;
  GtkWidget *button12;
  GtkWidget * general, * video_sound, * cart_memory, *advanced, * sound;
  GtkWidget * box;
  u8 perid;

  cores_to_range(SH2CoreList, &sh2interpreters);
  cores_to_range(M68KCoreList, &m68kinterpreters);
  cores_to_range(CDCoreList, &cdcores);
  cores_to_range(VIDCoreList, &vidcores);
  cores_to_range(OSDCoreList, &osdcores);
  cores_to_range(SNDCoreList, &sndcores);
  cores_to_range(PERCoreList, &percores);

  dialog1 = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (dialog1), "Yabause configuration");
  gtk_window_set_icon_name (GTK_WINDOW (dialog1), "gtk-preferences");
  gtk_window_set_type_hint (GTK_WINDOW (dialog1), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_resizable(GTK_WINDOW(dialog1), FALSE);

  notebook1 = gtk_notebook_new ();
  gtk_widget_show(notebook1);
  
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog1)->vbox), notebook1, TRUE, TRUE, 0);

  /*
   * General configuration
   */
  general = yui_page_new(keyfile);

  box = yui_page_add(YUI_PAGE(general), _("Bios"));
  gtk_container_add(GTK_CONTAINER(box), yui_file_entry_new(keyfile, "General", "BiosPath", YUI_FILE_ENTRY_BROWSE, NULL));

  box = yui_page_add(YUI_PAGE(general), _("Cdrom"));
  gtk_container_add(GTK_CONTAINER(box), yui_range_new(keyfile, "General", "CDROMCore", cdcores));
  gtk_container_add(GTK_CONTAINER(box), yui_file_entry_new(keyfile, "General", "CDROMDrive", YUI_FILE_ENTRY_BROWSE, NULL));

  box = yui_page_add(YUI_PAGE(general), _("Save States"));
  gtk_container_add(GTK_CONTAINER(box), yui_file_entry_new(keyfile, "General", "StatePath", YUI_FILE_ENTRY_BROWSE | YUI_FILE_ENTRY_DIRECTORY, NULL));
  
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), general, gtk_label_new (_("General")));
  gtk_widget_show_all(general);

  /*
   * Video configuration
   */
  video_sound = yui_page_new(keyfile);

  box = yui_page_add(YUI_PAGE(video_sound), _("Video Core"));
  gtk_container_add(GTK_CONTAINER(box), yui_range_new(keyfile, "General", "VideoCore", vidcores));

  box = yui_page_add(YUI_PAGE(video_sound), _("Bilinear Filtering"));
  {
    GtkWidget * bilinear = gtk_check_button_new_with_label("Enable Bilinear Filtering");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(bilinear), g_key_file_get_integer(keyfile, "General", "Bilinear", NULL));
    gtk_container_set_border_width(GTK_CONTAINER(bilinear), 10);
    g_signal_connect(bilinear, "toggled", G_CALLBACK(bilinear_toggled), NULL);
    gtk_container_add(GTK_CONTAINER(box), bilinear);
  }

#ifdef YAB_PORT_OSD
  box = yui_page_add(YUI_PAGE(video_sound), _("OSD Core"));
  gtk_container_add(GTK_CONTAINER(box), yui_range_new(keyfile, "General", "OSDCore", osdcores));
#endif

  box = yui_page_add(YUI_PAGE(video_sound), _("Resolution"));
  gtk_container_add(GTK_CONTAINER(box), yui_resolution_new(keyfile, "General"));

  box = yui_page_add(YUI_PAGE(video_sound), _("Video Format"));
  gtk_container_add(GTK_CONTAINER(box), yui_range_new(keyfile, "General", "VideoFormat", vidformats));

  box = yui_page_add(YUI_PAGE(video_sound), _("Frame Skip/Limiter"));
  {
    GtkWidget * frameskip = gtk_check_button_new_with_label("Enable frame skipping/limiting");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(frameskip), g_key_file_get_integer(keyfile, "General", "Frameskip", NULL));
    gtk_container_set_border_width(GTK_CONTAINER(frameskip), 10);
    g_signal_connect(frameskip, "toggled", G_CALLBACK(frameskip_toggled), NULL);
    gtk_container_add(GTK_CONTAINER(box), frameskip);
  }
  
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), video_sound, gtk_label_new (_("Video")));
  gtk_widget_show_all(video_sound);

  /*
   * Sound configuration
   */
  sound = yui_page_new(keyfile);

  box = yui_page_add(YUI_PAGE(sound), _("Sound Core"));
  gtk_container_add(GTK_CONTAINER(box), yui_range_new(keyfile, "General", "SoundCore", sndcores));

  {
    GtkWidget * volume;

    box = yui_page_add(YUI_PAGE(sound), _("Volume"));
    gtk_container_set_border_width(GTK_CONTAINER(box), 10);
    volume = gtk_hscale_new_with_range(0, 100, 1);
    gtk_range_set_value(GTK_RANGE(volume), g_key_file_get_integer(keyfile, "General", "Volume", NULL));
    g_signal_connect(volume, "value-changed", G_CALLBACK(volume_changed), NULL);
    gtk_container_add(GTK_CONTAINER(box), volume);
  }
  
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), sound, gtk_label_new (_("Sound")));
  gtk_widget_show_all(sound);

  /*
   * Cart/Memory configuration
   */
  cart_memory = yui_page_new(keyfile);
  
  box = yui_page_add(YUI_PAGE(cart_memory), _("Cartridge"));
  {
     GtkWidget * w1, * w2, * w3;

     w1 = yui_range_new(keyfile, "General", "CartType", carttypes);
     gtk_container_add(GTK_CONTAINER(box), w1);

     w2 = yui_file_entry_new(keyfile, "General", "CartPath", YUI_FILE_ENTRY_BROWSE, NULL);
     gtk_container_add(GTK_CONTAINER(box), w2);

     w3 = gtk_hbox_new(FALSE, 0);
     gtk_box_pack_start(GTK_BOX(w3), yui_file_entry_new(keyfile, "General", "NetlinkHost", 0, "Host"), TRUE, TRUE, 0);
     gtk_box_pack_start(GTK_BOX(w3), yui_file_entry_new(keyfile, "General", "NetlinkPort", 0, "Port"), TRUE, TRUE, 0);
     gtk_container_add(GTK_CONTAINER(box), w3);

     g_signal_connect(w1, "changed", G_CALLBACK(hide_show_cart_path), w2);
     g_signal_connect(w1, "changed", G_CALLBACK(hide_show_netlink), w3);
  
     box = yui_page_add(YUI_PAGE(cart_memory), _("Memory"));
     gtk_container_add(GTK_CONTAINER(box), yui_file_entry_new(keyfile, "General", "BackupRamPath", YUI_FILE_ENTRY_BROWSE, NULL));

     box = yui_page_add(YUI_PAGE(cart_memory), _("Mpeg ROM"));
     gtk_container_add(GTK_CONTAINER(box), yui_file_entry_new(keyfile, "General", "MpegRomPath", YUI_FILE_ENTRY_BROWSE, NULL));
  
     gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), cart_memory, gtk_label_new (_("Cart/Memory")));
     gtk_widget_show_all(cart_memory);

     if (yui_range_get_active(YUI_RANGE(w1)) == 8) gtk_widget_hide(w2); 
     else gtk_widget_hide(w3);
  }

  /*
   * Input Configuration
   */
  vbox17 = gtk_vbox_new (FALSE, 0);
  
  hbox22 = gtk_hbox_new (FALSE, 0);

  {
    GtkWidget * controllerscroll;
    GtkTreeStore * controllerlist;
    GtkWidget * controllerlistview;
    GtkCellRenderer * controllerrenderer;
    GtkTreeViewColumn * controllercolumn;
    GtkTreeIter iter;
    GtkTreePath * path;

    controllerscroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(controllerscroll), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    controllerlist = gtk_tree_store_new(1, G_TYPE_STRING);
    controllerlistview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(controllerlist));
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(controllerlistview), FALSE);

    controllerrenderer = gtk_cell_renderer_text_new();
    controllercolumn = gtk_tree_view_column_new_with_attributes("Controller", controllerrenderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (controllerlistview), controllercolumn);

    gtk_tree_store_append(controllerlist, &iter, NULL);
    gtk_tree_store_set(controllerlist, &iter, 0, "Pad", -1);

    gtk_tree_store_append(controllerlist, &iter, NULL);
    gtk_tree_store_set(controllerlist, &iter, 0, "Mouse", -1);

    gtk_container_add(GTK_CONTAINER(controllerscroll), controllerlistview);
    gtk_box_pack_start (GTK_BOX (hbox22), controllerscroll, TRUE, TRUE, 0);

    gtk_tree_view_expand_all(GTK_TREE_VIEW(controllerlistview));

    g_signal_connect(controllerlistview, "cursor-changed", G_CALLBACK(pertype_changed), hbox22);
    perid = g_key_file_get_integer(keyfile, "General", "PerType", NULL);
    switch(perid)
    {
       case PERMOUSE:
          path = gtk_tree_path_new_from_string("1");
          break;
       case PERPAD:
       default:
          path = gtk_tree_path_new_from_string("0");
          break;
    }
          
    gtk_tree_view_set_cursor(GTK_TREE_VIEW(controllerlistview), path, NULL, FALSE);
    gtk_tree_path_free(path);
  }
  
  gtk_box_pack_start (GTK_BOX (vbox17), hbox22, TRUE, TRUE, 0);

  //pertype_display_pad(hbox22);

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), vbox17, gtk_label_new (_("Input")));
  gtk_widget_show_all(vbox17);

  /*
   * Advanced configuration
   */

  advanced = yui_page_new(keyfile);
  
  box = yui_page_add(YUI_PAGE(advanced), _("Region"));
  gtk_container_add(GTK_CONTAINER(box), yui_range_new(keyfile, "General", "Region", regions));

  box = yui_page_add(YUI_PAGE(advanced), _("SH2 Interpreter"));
  gtk_container_add(GTK_CONTAINER(box), yui_range_new(keyfile, "General", "SH2Int", sh2interpreters));

  box = yui_page_add(YUI_PAGE(advanced), _("M68k Interpreter"));
  gtk_container_add(GTK_CONTAINER(box), yui_range_new(keyfile, "General", "M68kInt", m68kinterpreters));

  box = yui_page_add(YUI_PAGE(advanced), _("Audio Sync"));
  {
    GtkWidget *button = yui_check_button_new(
        _("Synchronize audio output with emulation"),
        keyfile, "General", "AudioSync"
    );
    gtk_container_add(GTK_CONTAINER(box), button);
    g_signal_connect(button, "changed",
                     G_CALLBACK(disable_enable_audio_sync), NULL);
  }

  box = yui_page_add(YUI_PAGE(advanced), _("Clock Sync"));
  {
    GtkWidget *button1, *button2;

    button1 = yui_check_button_new(
        _("Synchronize internal clock with emulation"),
        keyfile, "General", "ClockSync"
    );
    gtk_container_add(GTK_CONTAINER(box), button1);

    button2 = yui_check_button_new(
        _("Always start from 1998-01-01 12:00"),
        keyfile, "General", "FixedBaseTime"
    );
    gtk_container_add(GTK_CONTAINER(box), button2);
    if (!yui_check_button_get_active(YUI_CHECK_BUTTON(button1)))
      gtk_widget_set_sensitive(button2, FALSE);

    g_signal_connect(button1, "changed",
                     G_CALLBACK(disable_enable_fixed_base_time), button2);
  }

  box = yui_page_add(YUI_PAGE(advanced), _("Threads"));
  {
    GtkWidget *button = yui_check_button_new(
        _("Use multithreaded emulation (EXPERIMENTAL!)"),
        keyfile, "General", "UseThreads"
    );
    gtk_container_add(GTK_CONTAINER(box), button);
  }

#ifdef HAVE_LIBMINI18N
  box = yui_page_add(YUI_PAGE(advanced), _("Translation"));
  gtk_container_add(GTK_CONTAINER(box), yui_file_entry_new(keyfile, "General", "TranslationPath", YUI_FILE_ENTRY_BROWSE, NULL));
#endif
  
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), advanced, gtk_label_new (_("Advanced")));
  gtk_widget_show_all(advanced);

  /*
   * Dialog buttons
   */
  button11 = gtk_button_new_from_stock ("gtk-cancel");
  
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog1), button11, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (button11, GTK_CAN_DEFAULT);
  gtk_widget_show(button11);

  button12 = gtk_button_new_from_stock ("gtk-ok");
  
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog1), button12, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (button12, GTK_CAN_DEFAULT);
  gtk_widget_show(button12);

  gtk_widget_show(dialog1);

  return dialog1;
}
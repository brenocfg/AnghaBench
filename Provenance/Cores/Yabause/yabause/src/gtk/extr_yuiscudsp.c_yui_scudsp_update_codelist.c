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
typedef  int u32 ;
struct TYPE_3__ {int lastCode; int /*<<< orphan*/  uLabel; } ;
typedef  TYPE_1__ YuiScudsp ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScuDspDisasm (int,char*) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void yui_scudsp_update_codelist( YuiScudsp *scudsp, u32 addr) {
  /* refresh the assembler view. <addr> points the line to be highlighted. */

  int i;
  static char tagPC[] = "<span foreground=\"red\">";
  static char tagEnd[] = "</span>\n";
  char buf[100*24+40];
  char *curs = buf;
  char lineBuf[100];
  u32 offset;

  if ( addr - scudsp->lastCode >= 20 ) offset = addr - 8;
  else offset = scudsp->lastCode;
  scudsp->lastCode = offset;

  for (i=0; i < 24; i++) {

    if ( offset + i == addr ) { strcpy( curs, tagPC ); curs += strlen(tagPC); }
    ScuDspDisasm(offset+i, lineBuf);
    strcpy( curs, lineBuf );
    curs += strlen(lineBuf);
    if ( offset + i == addr ) { strcpy( curs, tagEnd ); curs += strlen(tagEnd); }
    else { strcpy( curs, "\n" ); curs += 1;}
  }
  *curs = 0;  

  gtk_label_set_markup( GTK_LABEL(scudsp->uLabel), buf );
}
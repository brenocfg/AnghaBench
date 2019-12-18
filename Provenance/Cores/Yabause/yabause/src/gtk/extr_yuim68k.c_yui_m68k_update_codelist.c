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
typedef  int u32 ;
struct TYPE_3__ {int lastCode; int /*<<< orphan*/  uLabel; } ;
typedef  TYPE_1__ YuiM68k ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ ) ; 
 int M68KDisasm (int,char*) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void yui_m68k_update_codelist( YuiM68k *m68k, u32 addr) {
  /* refrem68k the assembler view. <addr> points the line to be highlighted. */

  int i;
  static char tagPC[] = "<span foreground=\"red\">";
  static char tagEnd[] = "</span>\n";
  char buf[64*24+40];
  char *curs = buf;
  char lineBuf[64];
  u8 bOnPC = 0;
  u32 offset;

  if ( addr - m68k->lastCode >= 22 ) offset = addr;
  else offset = m68k->lastCode;
  m68k->lastCode = offset;

  for (i=0; i < 24; i++) {

    if ( offset == addr ) { bOnPC = 1; strcpy( curs, tagPC ); curs += strlen(tagPC); }
    offset = M68KDisasm(offset, lineBuf);
    strcpy( curs, lineBuf );
    curs += strlen(lineBuf);
    if ( bOnPC ) { bOnPC = 0; strcpy( curs, tagEnd ); curs += strlen(tagEnd); }
    else { strcpy( curs, "\n" ); curs += 1;}
  }
  *curs = 0;
  gtk_label_set_markup( GTK_LABEL(m68k->uLabel), buf );
}
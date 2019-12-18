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
typedef  int u32 ;
typedef  int /*<<< orphan*/  sh2regs_struct ;
struct TYPE_5__ {unsigned int addr; } ;
typedef  TYPE_1__ codebreakpoint_struct ;
struct TYPE_6__ {int lastCode; int /*<<< orphan*/  store; int /*<<< orphan*/  debugsh; } ;
typedef  TYPE_2__ YuiSh ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 char* GTK_STOCK_GO_FORWARD ; 
 char* GTK_STOCK_STOP ; 
 int MAX_BREAKPOINTS ; 
 int /*<<< orphan*/  MappedMemoryReadWord (int) ; 
 int /*<<< orphan*/  SH2Disasm (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* SH2GetBreakpointList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2GetRegisters (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned int*,char*) ; 

__attribute__((used)) static void SH2UpdateCodeList( YuiSh *sh2, u32 addr) {
  /* refresh the assembler view. <addr> points the line to be highlighted. */

  int i, j;
  char lineBuf[64];
  u32 offset;
  GtkTreeIter iter;
  unsigned int address;
  char address_s[20];
  char command_s[64];
  codebreakpoint_struct *cbp;
  sh2regs_struct sh2regs;

  gtk_list_store_clear(sh2->store);

  if ( addr - sh2->lastCode >= 20*2 ) offset = addr - (8*2);
  else offset = sh2->lastCode;
  sh2->lastCode = offset;

  cbp = SH2GetBreakpointList(sh2->debugsh);

  for (i = 0; i < 24; i++) {
    SH2GetRegisters(sh2->debugsh, &sh2regs);
    SH2Disasm(offset+2*i, MappedMemoryReadWord(offset+2*i), 0, &sh2regs, lineBuf);

    sscanf(lineBuf, "0x%8X: %[^\n]", &address, command_s);
    sprintf(address_s, "0x%08X", address);

    gtk_list_store_append(sh2->store, &iter);
    if ( offset + 2*i == addr ) {
      gtk_list_store_set(sh2->store, &iter, 0, GTK_STOCK_GO_FORWARD, -1);
    } else {
      for (j = 0;j < MAX_BREAKPOINTS - 1;j++) {
        if (cbp[j].addr == address) {
          gtk_list_store_set(sh2->store, &iter, 0, GTK_STOCK_STOP, -1);
        }
      }
    }

    gtk_list_store_set(sh2->store, &iter, 1, address_s, -1);

    gtk_list_store_set(sh2->store, &iter, 2, command_s, -1);
  }
}
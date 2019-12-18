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
typedef  int /*<<< orphan*/  rompath ;
typedef  int /*<<< orphan*/  of ;
struct TYPE_4__ {int lStructSize; char* lpstrFilter; char* lpstrFile; int nMaxFile; int Flags; int /*<<< orphan*/  hwndOwner; } ;
typedef  TYPE_1__ OPENFILENAME ;

/* Variables and functions */
 int /*<<< orphan*/  FrameWnd ; 
 int /*<<< orphan*/  GetOpenFileName (TYPE_1__*) ; 
 int MAX_PATH ; 
 int OFN_FILEMUSTEXIST ; 
 int OFN_HIDEREADONLY ; 
 scalar_t__ PGS_Paused ; 
 scalar_t__ PGS_Running ; 
 int /*<<< orphan*/  PrepareForROM () ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int emu_reload_rom (char*) ; 
 scalar_t__ engineState ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  loop_end_event ; 
 int /*<<< orphan*/  loop_enter_event ; 
 int /*<<< orphan*/  rom_fname_loaded ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void LoadROM(const char *cmdpath)
{
  char rompath[MAX_PATH];
  int ret;

  if (cmdpath != NULL && strlen(cmdpath)) {
    strcpy(rompath, cmdpath + (cmdpath[0] == '\"' ? 1 : 0));
    if (rompath[strlen(rompath)-1] == '\"')
      rompath[strlen(rompath)-1] = 0;
  }
  else {
    OPENFILENAME of; ZeroMemory(&of, sizeof(of));
    rompath[sizeof(rompath) - 1] = 0;
    strncpy(rompath, rom_fname_loaded, sizeof(rompath) - 1);
    of.lStructSize = sizeof(of);
    of.lpstrFilter = "ROMs, CD images\0*.smd;*.bin;*.gen;*.zip;*.32x;*.sms;*.iso;*.cso;*.cue\0"
                     "whatever\0*.*\0";
    of.lpstrFile = rompath;
    of.nMaxFile = MAX_PATH;
    of.Flags = OFN_FILEMUSTEXIST|OFN_HIDEREADONLY;
    of.hwndOwner = FrameWnd;
    if (!GetOpenFileName(&of))
      return;
  }

  if (engineState == PGS_Running) {
    engineState = PGS_Paused;
    WaitForSingleObject(loop_end_event, 5000);
  }

  ret = emu_reload_rom(rompath);
  if (ret == 0) {
    extern char menu_error_msg[]; // HACK..
    error(menu_error_msg);
    return;
  }

  PrepareForROM();
  engineState = PGS_Running;
  SetEvent(loop_enter_event);
}
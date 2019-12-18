#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pint_ret_t ;
typedef  int /*<<< orphan*/  path ;
struct TYPE_2__ {int* pen_pos; scalar_t__ page; } ;

/* Variables and functions */
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DrawMenuBar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableMenuItem (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FrameWnd ; 
 int /*<<< orphan*/  GetModuleFileName (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int MF_BYPOSITION ; 
 int /*<<< orphan*/  MF_CHECKED ; 
 int MF_ENABLED ; 
 int MF_GRAYED ; 
 int /*<<< orphan*/  MF_UNCHECKED ; 
 int PAHW_PICO ; 
 int /*<<< orphan*/  PI_ROM ; 
 int PicoAHW ; 
 int /*<<< orphan*/  PicoGetInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PicoPadWnd ; 
 TYPE_1__ PicoPicohw ; 
 int /*<<< orphan*/  PicoSwWnd ; 
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOWNA ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_COMMAND ; 
 int /*<<< orphan*/  check_name_alias (char*) ; 
 int extract_rom_name (char*,unsigned char*,int) ; 
 scalar_t__ in_vk_add_pl12 ; 
 int /*<<< orphan*/  mmain ; 
 int /*<<< orphan*/  mpicohw ; 
 void* png2hb (char*,int) ; 
 int /*<<< orphan*/ * ppad_bmp ; 
 int /*<<< orphan*/ ** ppage_bmps ; 
 char* rom_name ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void PrepareForROM(void)
{
  unsigned char *rom_data = NULL;
  int i, ret, show = PicoAHW & PAHW_PICO;
  
  PicoGetInternal(PI_ROM, (pint_ret_t *) &rom_data);
  EnableMenuItem(mmain, 2, MF_BYPOSITION|(show ? MF_ENABLED : MF_GRAYED));
  ShowWindow(PicoPadWnd, show ? SW_SHOWNA : SW_HIDE);
  ShowWindow(PicoSwWnd, show ? SW_SHOWNA : SW_HIDE);
  CheckMenuItem(mpicohw, 1210, show ? MF_CHECKED : MF_UNCHECKED);
  CheckMenuItem(mpicohw, 1211, show ? MF_CHECKED : MF_UNCHECKED);
  PostMessage(FrameWnd, WM_COMMAND, 1220 + PicoPicohw.page, 0);
  DrawMenuBar(FrameWnd);
  InvalidateRect(PicoSwWnd, NULL, 1);

  PicoPicohw.pen_pos[0] =
  PicoPicohw.pen_pos[1] = 0x8000;
  in_vk_add_pl12 = 0;

  ret = extract_rom_name(rom_name, rom_data + 0x150, 0x20);
  if (ret == 0)
    extract_rom_name(rom_name, rom_data + 0x130, 0x20);

  if (show)
  {
    char path[MAX_PATH], *p;
    GetModuleFileName(NULL, path, sizeof(path) - 32);
    p = strrchr(path, '\\');
    if (p == NULL) p = path;
    else p++;
    if (ppad_bmp == NULL) {
      strcpy(p, "pico\\pad.png");
      ppad_bmp = png2hb(path, 0);
    }

    strcpy(p, "pico\\alias.txt");
    check_name_alias(path);

    for (i = 0; i < 7; i++) {
      if (ppage_bmps[i] != NULL) DeleteObject(ppage_bmps[i]);
      sprintf(p, "pico\\%s_%i.png", rom_name, i);
      ppage_bmps[i] = png2hb(path, 1);
    }
    // games usually don't have page 6, so just duplicate page 5.
    if (ppage_bmps[6] == NULL && ppage_bmps[5] != NULL) {
      sprintf(p, "pico\\%s_5.png", rom_name);
      ppage_bmps[6] = png2hb(path, 1);
    }
  }
}
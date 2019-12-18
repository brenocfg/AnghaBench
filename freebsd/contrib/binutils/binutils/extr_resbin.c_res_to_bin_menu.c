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
typedef  int /*<<< orphan*/  windres_bfd ;
struct bin_menuex {int /*<<< orphan*/  help; int /*<<< orphan*/  sig2; int /*<<< orphan*/  sig1; } ;
struct bin_menu {int /*<<< orphan*/  help; int /*<<< orphan*/  sig2; int /*<<< orphan*/  sig1; } ;
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_4__ {int /*<<< orphan*/  items; int /*<<< orphan*/  help; } ;
typedef  TYPE_1__ rc_menu ;

/* Variables and functions */
 scalar_t__ BIN_MENUEX_SIZE ; 
 scalar_t__ BIN_MENU_SIZE ; 
 int extended_menu (TYPE_1__ const*) ; 
 int /*<<< orphan*/  res_to_bin_menuexitems (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_menuitems (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,struct bin_menuex*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  windres_put_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  windres_put_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rc_uint_type
res_to_bin_menu (windres_bfd *wrbfd, rc_uint_type off, const rc_menu *menu)
{
  int menuex;

  menuex = extended_menu (menu);

  if (wrbfd)
    {
  if (! menuex)
    {
	  struct bin_menu bm;
	  windres_put_16 (wrbfd, bm.sig1, 0);
	  windres_put_16 (wrbfd, bm.sig2, 0);
	  set_windres_bfd_content (wrbfd, &bm, off, BIN_MENU_SIZE);
    }
  else
    {
	  struct bin_menuex bm;
	  windres_put_16 (wrbfd, bm.sig1, 1);
	  windres_put_16 (wrbfd, bm.sig2, 4);
	  windres_put_32 (wrbfd, bm.help, menu->help);
	  set_windres_bfd_content (wrbfd, &bm, off, BIN_MENUEX_SIZE);
    }
    }
  off += (menuex != 0 ? BIN_MENUEX_SIZE : BIN_MENU_SIZE);
  if (! menuex)
    {
      off = res_to_bin_menuitems (wrbfd, off, menu->items);
    }
  else
    {
      off = res_to_bin_menuexitems (wrbfd, off, menu->items);
    }
  return off;
}
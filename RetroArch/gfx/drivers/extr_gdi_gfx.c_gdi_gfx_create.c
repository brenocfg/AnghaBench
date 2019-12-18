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
typedef  int /*<<< orphan*/  os ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_os ) (char*,int,int*,int*) ;} ;
typedef  TYPE_1__ frontend_ctx_driver_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 TYPE_1__* frontend_get_ptr () ; 
 int gdi_lte_win98 ; 
 int gdi_win_major ; 
 int gdi_win_minor ; 
 int /*<<< orphan*/  stub1 (char*,int,int*,int*) ; 

__attribute__((used)) static void gdi_gfx_create(void)
{
   char os[64] = {0};

   frontend_ctx_driver_t *ctx = frontend_get_ptr();

   if (!ctx || !ctx->get_os)
   {
      RARCH_ERR("[GDI] No frontend driver found.\n");
      return;
   }

   ctx->get_os(os, sizeof(os), &gdi_win_major, &gdi_win_minor);

   /* Are we running on Windows 98 or below? */
   if (gdi_win_major < 4 || (gdi_win_major == 4 && gdi_win_minor <= 10))
   {
      RARCH_LOG("[GDI] Win98 or lower detected, using slow frame conversion method for RGB444.\n");
      gdi_lte_win98 = true;
   }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ VCOS_STATUS_T ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 scalar_t__ gx_priv_font_init (char const*) ; 
 scalar_t__ gx_priv_initialise () ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

VCOS_STATUS_T gx_graphics_init(const char *font_dir)
{
   GX_CLIENT_STATE_T save;
   VCOS_STATUS_T rc;

   gx_priv_save(&save, NULL);

   rc = gx_priv_initialise();
   if (rc == VCOS_SUCCESS)
      rc = gx_priv_font_init(font_dir);

   gx_priv_restore(&save);

   return rc;
}
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
typedef  void ui_companion_win32_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 

__attribute__((used)) static void *ui_companion_win32_init(void)
{
   ui_companion_win32_t *handle = (ui_companion_win32_t*)
      calloc(1, sizeof(*handle));

   if (!handle)
      return NULL;

   return handle;
}
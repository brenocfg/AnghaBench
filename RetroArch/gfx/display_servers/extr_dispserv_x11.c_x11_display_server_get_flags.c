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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT32_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISPSERV_CTX_CRT_SWITCHRES ; 

__attribute__((used)) static uint32_t x11_display_server_get_flags(void *data)
{
   uint32_t             flags   = 0;

#ifdef HAVE_XRANDR
   BIT32_SET(flags, DISPSERV_CTX_CRT_SWITCHRES);
#endif

   return flags;
}
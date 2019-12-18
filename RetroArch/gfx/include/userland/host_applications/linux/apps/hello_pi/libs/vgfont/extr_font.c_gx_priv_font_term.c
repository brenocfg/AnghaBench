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
struct TYPE_2__ {int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 TYPE_1__ default_font ; 
 int /*<<< orphan*/  gx_font_cache_flush () ; 
 int /*<<< orphan*/  vcos_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgft_term () ; 

void gx_priv_font_term(void)
{
   gx_font_cache_flush();
   vgft_term();
   vcos_free(default_font.mem);
}
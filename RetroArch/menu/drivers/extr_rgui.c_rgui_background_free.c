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
struct TYPE_2__ {int /*<<< orphan*/ * data; scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__ rgui_background_buf ; 

__attribute__((used)) static void rgui_background_free(void)
{
   rgui_background_buf.width = 0;
   rgui_background_buf.height = 0;
   
   if (rgui_background_buf.data)
      free(rgui_background_buf.data);
   rgui_background_buf.data = NULL;
}
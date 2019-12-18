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
struct TYPE_4__ {int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gint ;

/* Variables and functions */
 int /*<<< orphan*/  subtitle_exclusive_burn_settings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subtitle_refresh_list_ui (TYPE_1__*) ; 

__attribute__((used)) static void
subtitle_exclusive_burn(signal_user_data_t *ud, gint index)
{
    subtitle_exclusive_burn_settings(ud->settings, index);
    subtitle_refresh_list_ui(ud);
}
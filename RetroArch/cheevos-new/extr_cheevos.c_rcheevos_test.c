#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cheevos_leaderboards_enable; scalar_t__ cheevos_hardcore_mode_enable; scalar_t__ cheevos_test_unofficial; } ;
struct TYPE_5__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  rcheevos_hardcore_paused ; 
 int /*<<< orphan*/  rcheevos_test_cheevo_set (int) ; 
 int /*<<< orphan*/  rcheevos_test_leaderboards () ; 

void rcheevos_test(void)
{
   settings_t *settings = config_get_ptr();

   rcheevos_test_cheevo_set(true);

   if (settings)
   {
      if (settings->bools.cheevos_test_unofficial)
         rcheevos_test_cheevo_set(false);

      if (settings->bools.cheevos_hardcore_mode_enable &&
          settings->bools.cheevos_leaderboards_enable  &&
          !rcheevos_hardcore_paused)
         rcheevos_test_leaderboards();
   }
}
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
struct TYPE_2__ {int start_time; int /*<<< orphan*/  str_name; } ;

/* Variables and functions */
 int g_i_hwm ; 
 TYPE_1__* g_tag ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int Nested (char* str_tag) {
  int i ;
  for (i = 0; i < g_i_hwm; ++i) {
    if (strcmp (g_tag [i].str_name, str_tag) == 0 && g_tag [i].start_time > -1) {
      /* Already 'running': nested*/
      return 1 ;
    }
  }
  /* Not running: not nested */
  return 0 ;
}
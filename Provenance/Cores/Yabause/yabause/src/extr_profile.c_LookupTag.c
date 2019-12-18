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
struct TYPE_4__ {int /*<<< orphan*/  str_name; } ;
typedef  TYPE_1__ entry_t ;

/* Variables and functions */
 int g_i_hwm ; 
 TYPE_1__* g_tag ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static entry_t* LookupTag (char* str_tag) {
  int i ;
  for (i = 0; i < g_i_hwm; ++i) {
    if (strcmp (g_tag [i].str_name, str_tag) == 0) {
      return &g_tag [i] ;
    }
  }
  return 0 ;
}
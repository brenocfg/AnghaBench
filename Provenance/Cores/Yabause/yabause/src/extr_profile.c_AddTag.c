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
struct TYPE_4__ {int start_time; int /*<<< orphan*/  str_name; } ;
typedef  TYPE_1__ entry_t ;

/* Variables and functions */
 int NUM_TAGS ; 
 int g_i_hwm ; 
 TYPE_1__* g_tag ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static entry_t* AddTag (char* str_tag) {
  if (g_i_hwm + 1 == NUM_TAGS) {
    /* Full */
    return 0 ;
  }
  /* Copy the name */
  strcpy (g_tag [g_i_hwm].str_name, str_tag) ;
  g_tag [g_i_hwm].start_time = -1 ;
  /* Increase the high-water-mark but return the current index */
  return &g_tag [g_i_hwm++] ;
}
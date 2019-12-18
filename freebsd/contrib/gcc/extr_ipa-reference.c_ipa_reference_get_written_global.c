#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* ipa_reference_global_vars_info_t ;
typedef  int /*<<< orphan*/ * bitmap ;
struct TYPE_3__ {int /*<<< orphan*/ * statics_written; } ;

/* Variables and functions */
 TYPE_1__* get_global_reference_vars_info (int /*<<< orphan*/ ) ; 

bitmap 
ipa_reference_get_written_global (tree fn) 
{
  ipa_reference_global_vars_info_t g = get_global_reference_vars_info (fn);
  if (g) 
    return g->statics_written;
  else
    return NULL;
}
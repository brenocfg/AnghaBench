#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* ipa_reference_vars_info_t ;
typedef  int /*<<< orphan*/ * ipa_reference_local_vars_info_t ;
struct TYPE_4__ {TYPE_1__* reference_vars_info; } ;
struct TYPE_3__ {int /*<<< orphan*/ * local; } ;

/* Variables and functions */
 TYPE_2__* get_function_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ipa_reference_local_vars_info_t
get_local_reference_vars_info (tree fn) 
{
  ipa_reference_vars_info_t info = get_function_ann (fn)->reference_vars_info;

  if (info)
    return info->local;
  else
    /* This phase was not run.  */ 
    return NULL;
}
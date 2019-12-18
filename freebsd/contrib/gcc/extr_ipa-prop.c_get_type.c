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
struct ipa_jump_func {int type; } ;
typedef  enum jump_func_type { ____Placeholder_jump_func_type } jump_func_type ;

/* Variables and functions */

enum jump_func_type
get_type (struct ipa_jump_func *jf)
{
  return jf->type;
}
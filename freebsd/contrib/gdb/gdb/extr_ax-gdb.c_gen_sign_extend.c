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
struct type {int dummy; } ;
struct agent_expr {int dummy; } ;

/* Variables and functions */
 int TARGET_CHAR_BIT ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (struct type*) ; 
 int /*<<< orphan*/  ax_ext (struct agent_expr*,int) ; 

__attribute__((used)) static void
gen_sign_extend (struct agent_expr *ax, struct type *type)
{
  /* Do we need to sign-extend this?  */
  if (!TYPE_UNSIGNED (type))
    ax_ext (ax, TYPE_LENGTH (type) * TARGET_CHAR_BIT);
}
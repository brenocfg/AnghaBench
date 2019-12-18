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
typedef  int /*<<< orphan*/  tree ;
struct loop {int dummy; } ;
struct iv_cand {int /*<<< orphan*/  var_before; int /*<<< orphan*/  var_after; } ;

/* Variables and functions */
 scalar_t__ stmt_after_increment (struct loop*,struct iv_cand*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
var_at_stmt (struct loop *loop, struct iv_cand *cand, tree stmt)
{
  if (stmt_after_increment (loop, cand, stmt))
    return cand->var_after;
  else
    return cand->var_before;
}
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
struct iv_use {int /*<<< orphan*/  stmt; } ;
struct iv_cand {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_computation_at (struct loop*,struct iv_use*,struct iv_cand*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
get_computation (struct loop *loop, struct iv_use *use, struct iv_cand *cand)
{
  return get_computation_at (loop, use, cand, use->stmt);
}
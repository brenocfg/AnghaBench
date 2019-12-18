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
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  int /*<<< orphan*/  tree ;
struct lower_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_stmt (int /*<<< orphan*/ *,struct lower_data*) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lower_stmt_body (tree expr, struct lower_data *data)
{
  tree_stmt_iterator tsi;

  for (tsi = tsi_start (expr); !tsi_end_p (tsi); )
    lower_stmt (&tsi, data);
}
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
struct expr {struct expr* next_same_hash; int /*<<< orphan*/  expr; } ;

/* Variables and functions */
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct expr *
next_set (unsigned int regno, struct expr *expr)
{
  do
    expr = expr->next_same_hash;
  while (expr && REGNO (SET_DEST (expr->expr)) != regno);

  return expr;
}
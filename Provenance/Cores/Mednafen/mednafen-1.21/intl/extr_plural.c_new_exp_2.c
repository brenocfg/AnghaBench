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
struct expression {int dummy; } ;
typedef  enum expression_operator { ____Placeholder_expression_operator } expression_operator ;

/* Variables and functions */
 struct expression* new_exp (int,int,struct expression**) ; 

__attribute__((used)) static struct expression *
new_exp_2 (enum expression_operator op, struct expression *left,
	   struct expression *right)
{
  struct expression *args[2];

  args[0] = left;
  args[1] = right;
  return new_exp (2, op, args);
}
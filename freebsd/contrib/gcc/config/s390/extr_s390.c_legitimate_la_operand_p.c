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
struct s390_address {scalar_t__ pointer; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ TARGET_64BIT ; 
 int /*<<< orphan*/  s390_decompose_address (int /*<<< orphan*/ ,struct s390_address*) ; 

bool
legitimate_la_operand_p (rtx op)
{
  struct s390_address addr;
  if (!s390_decompose_address (op, &addr))
    return false;

  return (TARGET_64BIT || addr.pointer);
}
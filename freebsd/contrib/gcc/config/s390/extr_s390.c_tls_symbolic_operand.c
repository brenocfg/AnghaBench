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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF ; 
 int SYMBOL_REF_TLS_MODEL (int /*<<< orphan*/ ) ; 

int
tls_symbolic_operand (rtx op)
{
  if (GET_CODE (op) != SYMBOL_REF)
    return 0;
  return SYMBOL_REF_TLS_MODEL (op);
}
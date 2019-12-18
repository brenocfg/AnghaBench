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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_VECTOR_ELT (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ V2SFmode ; 
 scalar_t__ V4SFmode ; 
 int /*<<< orphan*/  gen_lowpart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HOST_WIDE_INT
const_vector_elt_as_int (rtx op, unsigned int elt)
{
  rtx tmp = CONST_VECTOR_ELT (op, elt);
  if (GET_MODE (op) == V4SFmode
      || GET_MODE (op) == V2SFmode)
    tmp = gen_lowpart (SImode, tmp);
  return INTVAL (tmp);
}
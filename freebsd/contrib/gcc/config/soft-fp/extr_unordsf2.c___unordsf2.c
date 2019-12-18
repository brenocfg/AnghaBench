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
typedef  int /*<<< orphan*/  SFtype ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  FP_CMP_UNORD_S (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_RAW_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
__unordsf2(SFtype a, SFtype b)
{
  FP_DECL_S(A);
  FP_DECL_S(B);
  int r;

  FP_UNPACK_RAW_S(A, a);
  FP_UNPACK_RAW_S(B, b);
  FP_CMP_UNORD_S(r, A, B);

  return r;
}
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
typedef  int /*<<< orphan*/  TFtype ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  FP_CMP_UNORD_Q (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_Q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_RAW_Q (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
__unordtf2(TFtype a, TFtype b)
{
  FP_DECL_Q(A);
  FP_DECL_Q(B);
  int r;

  FP_UNPACK_RAW_Q(A, a);
  FP_UNPACK_RAW_Q(B, b);
  FP_CMP_UNORD_Q(r, A, B);

  return r;
}
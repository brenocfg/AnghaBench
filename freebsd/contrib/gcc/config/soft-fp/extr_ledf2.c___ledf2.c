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
typedef  int /*<<< orphan*/  DFtype ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  FP_CMP_D (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_EX_INVALID ; 
 int /*<<< orphan*/  FP_HANDLE_EXCEPTIONS ; 
 scalar_t__ FP_ISSIGNAN_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_SET_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_RAW_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __ledf2(DFtype a, DFtype b)
{
  FP_DECL_EX;
  FP_DECL_D(A); FP_DECL_D(B);
  int r;

  FP_UNPACK_RAW_D(A, a);
  FP_UNPACK_RAW_D(B, b);
  FP_CMP_D(r, A, B, 2);
  if (r == 2 && (FP_ISSIGNAN_D(A) || FP_ISSIGNAN_D(B)))
    FP_SET_EXCEPTION(FP_EX_INVALID);
  FP_HANDLE_EXCEPTIONS;

  return r;
}
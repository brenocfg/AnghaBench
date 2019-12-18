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
typedef  int /*<<< orphan*/  SFtype ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_Q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_HANDLE_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_INIT_ROUNDMODE ; 
 int /*<<< orphan*/  FP_PACK_SEMIRAW_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_TRUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_SEMIRAW_Q (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  S ; 

SFtype __trunctfsf2(TFtype a)
{
  FP_DECL_EX;
  FP_DECL_Q(A);
  FP_DECL_S(R);
  SFtype r;

  FP_INIT_ROUNDMODE;
  FP_UNPACK_SEMIRAW_Q(A, a);
#if (2 * _FP_W_TYPE_SIZE) < _FP_FRACBITS_Q
  FP_TRUNC(S,Q,1,4,R,A);
#else
  FP_TRUNC(S,Q,1,2,R,A);
#endif
  FP_PACK_SEMIRAW_S(r, R);
  FP_HANDLE_EXCEPTIONS;

  return r;
}
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
typedef  int /*<<< orphan*/  DFtype ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_EXTEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_HANDLE_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_INIT_ROUNDMODE ; 
 int /*<<< orphan*/  FP_PACK_RAW_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_RAW_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  S ; 

DFtype __extendsfdf2(SFtype a)
{
  FP_DECL_EX;
  FP_DECL_S(A);
  FP_DECL_D(R);
  DFtype r;

  FP_INIT_ROUNDMODE;
  FP_UNPACK_RAW_S(A, a);
#if _FP_W_TYPE_SIZE < _FP_FRACBITS_D
  FP_EXTEND(D,S,2,1,R,A);
#else
  FP_EXTEND(D,S,1,1,R,A);
#endif
  FP_PACK_RAW_D(r, R);
  FP_HANDLE_EXCEPTIONS;

  return r;
}
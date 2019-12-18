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
typedef  int /*<<< orphan*/  UDItype ;
typedef  int /*<<< orphan*/  TFtype ;
typedef  int /*<<< orphan*/  DItype ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  DI_BITS ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_Q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_HANDLE_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_TO_INT_Q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FP_UNPACK_RAW_Q (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DItype __fixtfdi(TFtype a)
{
  FP_DECL_EX;
  FP_DECL_Q(A);
  UDItype r;

  FP_UNPACK_RAW_Q(A, a);
  FP_TO_INT_Q(r, A, DI_BITS, 1);
  FP_HANDLE_EXCEPTIONS;

  return r;
}
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
typedef  int /*<<< orphan*/  SItype ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_Q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_FROM_INT_Q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_HANDLE_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_PACK_RAW_Q (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_BITS ; 
 int /*<<< orphan*/  USItype ; 

TFtype __floatsitf(SItype i)
{
  FP_DECL_EX;
  FP_DECL_Q(A);
  TFtype a;

  FP_FROM_INT_Q(A, i, SI_BITS, USItype);
  FP_PACK_RAW_Q(a, A);
  FP_HANDLE_EXCEPTIONS;

  return a;
}
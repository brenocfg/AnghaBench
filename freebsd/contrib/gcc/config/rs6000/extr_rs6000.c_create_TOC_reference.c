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
 int /*<<< orphan*/  Pmode ; 
 size_t TOC_REGISTER ; 
 int /*<<< orphan*/  gen_rtx_CONST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MINUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ no_new_pseudos ; 
 int* regs_ever_live ; 
 int /*<<< orphan*/  toc_label_name ; 

rtx
create_TOC_reference (rtx symbol)
{
  if (no_new_pseudos)
    regs_ever_live[TOC_REGISTER] = 1;
  return gen_rtx_PLUS (Pmode,
	   gen_rtx_REG (Pmode, TOC_REGISTER),
	     gen_rtx_CONST (Pmode,
	       gen_rtx_MINUS (Pmode, symbol,
		 gen_rtx_SYMBOL_REF (Pmode, toc_label_name))));
}
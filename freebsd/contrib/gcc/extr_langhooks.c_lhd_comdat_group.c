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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 char const* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 

const char *
lhd_comdat_group (tree decl)
{
  return IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl));
}
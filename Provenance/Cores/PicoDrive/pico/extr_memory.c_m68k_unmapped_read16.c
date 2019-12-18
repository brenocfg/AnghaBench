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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EL_UIO ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 m68k_unmapped_read16(u32 a)
{
  elprintf(EL_UIO, "m68k unmapped r16 [%06x] @%06x", a, SekPc);
  return 0;
}
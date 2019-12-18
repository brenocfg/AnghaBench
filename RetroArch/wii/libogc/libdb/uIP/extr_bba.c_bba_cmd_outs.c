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
 int /*<<< orphan*/  bba_cmd_outsnosel (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bba_deselect () ; 
 int /*<<< orphan*/  bba_select () ; 

__attribute__((used)) static void bba_cmd_outs(u32 reg,void *val,u32 len)
{
	bba_select();
	bba_cmd_outsnosel(reg,val,len);
	bba_deselect();
}
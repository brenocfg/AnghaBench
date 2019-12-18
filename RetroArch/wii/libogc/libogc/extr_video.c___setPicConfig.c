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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  VI_REGCHANGE (int) ; 
 scalar_t__ VI_XFBMODE_DF ; 
 int /*<<< orphan*/  changed ; 
 int* regs ; 

__attribute__((used)) static inline void __setPicConfig(u16 fbSizeX,u32 xfbMode,u16 panPosX,u16 panSizeX,u8 *wordPerLine,u8 *std,u8 *wpl,u8 *xof)
{
	*wordPerLine = (fbSizeX+15)/16;
	*std = *wordPerLine;
	if(xfbMode==VI_XFBMODE_DF) *std <<= 1;

	*xof = panPosX%16;
	*wpl = (*xof+(panSizeX+15))/16;
	regs[36] = (*wpl<<8)|*std;
	changed |= VI_REGCHANGE(36);
}
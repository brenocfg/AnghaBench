#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
struct TYPE_2__ {size_t r; size_t g; size_t b; } ;

/* Variables and functions */
 TYPE_1__* psdl ; 

void FCEUD_GetPalette(uint8 index, uint8 *r, uint8 *g, uint8 *b)
{
 *r=psdl[index].r;
 *g=psdl[index].g;
 *b=psdl[index].b;
}
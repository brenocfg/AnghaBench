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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fbcon_putcs (struct vc_data*,unsigned short*,int,int,int) ; 
 int /*<<< orphan*/  scr_writew (int,unsigned short*) ; 

__attribute__((used)) static void fbcon_putc(struct vc_data *vc, int c, int ypos, int xpos)
{
	unsigned short chr;

	scr_writew(c, &chr);
	fbcon_putcs(vc, &chr, 1, ypos, xpos);
}
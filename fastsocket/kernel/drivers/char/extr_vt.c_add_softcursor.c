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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int type ;
struct vc_data {int vc_cursor_type; int /*<<< orphan*/  vc_x; int /*<<< orphan*/  vc_y; TYPE_1__* vc_sw; scalar_t__ vc_pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* con_putc ) (struct vc_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ DO_UPDATE (struct vc_data*) ; 
 int scr_readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scr_writew (int,int /*<<< orphan*/ *) ; 
 int softcursor_original ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_softcursor(struct vc_data *vc)
{
	int i = scr_readw((u16 *) vc->vc_pos);
	u32 type = vc->vc_cursor_type;

	if (! (type & 0x10)) return;
	if (softcursor_original != -1) return;
	softcursor_original = i;
	i |= ((type >> 8) & 0xff00 );
	i ^= ((type) & 0xff00 );
	if ((type & 0x20) && ((softcursor_original & 0x7000) == (i & 0x7000))) i ^= 0x7000;
	if ((type & 0x40) && ((i & 0x700) == ((i & 0x7000) >> 4))) i ^= 0x0700;
	scr_writew(i, (u16 *) vc->vc_pos);
	if (DO_UPDATE(vc))
		vc->vc_sw->con_putc(vc, i, vc->vc_y, vc->vc_x);
}
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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {int vc_rows; int /*<<< orphan*/  vc_video_erase_char; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDA_ADDR (int /*<<< orphan*/ ,int) ; 
#define  SM_DOWN 129 
#define  SM_UP 128 
 int /*<<< orphan*/  mda_convert_attr (int /*<<< orphan*/ ) ; 
 int mda_num_columns ; 
 int /*<<< orphan*/  scr_memmovew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scr_memsetw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mdacon_scroll(struct vc_data *c, int t, int b, int dir, int lines)
{
	u16 eattr = mda_convert_attr(c->vc_video_erase_char);

	if (!lines)
		return 0;

	if (lines > c->vc_rows)   /* maximum realistic size */
		lines = c->vc_rows;

	switch (dir) {

	case SM_UP:
		scr_memmovew(MDA_ADDR(0,t), MDA_ADDR(0,t+lines),
				(b-t-lines)*mda_num_columns*2);
		scr_memsetw(MDA_ADDR(0,b-lines), eattr,
				lines*mda_num_columns*2);
		break;

	case SM_DOWN:
		scr_memmovew(MDA_ADDR(0,t+lines), MDA_ADDR(0,t),
				(b-t-lines)*mda_num_columns*2);
		scr_memsetw(MDA_ADDR(0,t), eattr, lines*mda_num_columns*2);
		break;
	}

	return 0;
}
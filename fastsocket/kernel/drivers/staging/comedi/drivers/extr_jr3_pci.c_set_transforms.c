#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct transform_t {TYPE_3__* link; } ;
struct jr3_channel {TYPE_2__* transforms; } ;
struct TYPE_6__ {scalar_t__ link_type; int /*<<< orphan*/  link_amount; } ;
struct TYPE_5__ {TYPE_1__* link; } ;
struct TYPE_4__ {int /*<<< orphan*/  link_amount; int /*<<< orphan*/  link_type; } ;

/* Variables and functions */
 scalar_t__ end_x_form ; 
 int /*<<< orphan*/  set_s16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_u16 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void set_transforms(volatile struct jr3_channel *channel,
			   struct transform_t transf, short num)
{
	int i;

	num &= 0x000f;		/*  Make sure that 0 <= num <= 15 */
	for (i = 0; i < 8; i++) {

		set_u16(&channel->transforms[num].link[i].link_type,
			transf.link[i].link_type);
		udelay(1);
		set_s16(&channel->transforms[num].link[i].link_amount,
			transf.link[i].link_amount);
		udelay(1);
		if (transf.link[i].link_type == end_x_form) {
			break;
		}
	}
}
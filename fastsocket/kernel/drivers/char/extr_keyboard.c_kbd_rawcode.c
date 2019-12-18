#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int dummy; } ;
struct TYPE_5__ {scalar_t__ kbdmode; } ;
struct TYPE_4__ {struct vc_data* d; } ;

/* Variables and functions */
 scalar_t__ VC_RAW ; 
 size_t fg_console ; 
 TYPE_2__* kbd ; 
 TYPE_2__* kbd_table ; 
 int /*<<< orphan*/  put_queue (struct vc_data*,unsigned char) ; 
 TYPE_1__* vc_cons ; 

__attribute__((used)) static void kbd_rawcode(unsigned char data)
{
	struct vc_data *vc = vc_cons[fg_console].d;
	kbd = kbd_table + fg_console;
	if (kbd->kbdmode == VC_RAW)
		put_queue(vc, data);
}
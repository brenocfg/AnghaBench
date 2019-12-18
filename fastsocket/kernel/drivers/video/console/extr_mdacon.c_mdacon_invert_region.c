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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int scr_readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scr_writew (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mdacon_invert_region(struct vc_data *c, u16 *p, int count)
{
	for (; count > 0; count--) {
		scr_writew(scr_readw(p) ^ 0x0800, p);
		p++;
	}
}
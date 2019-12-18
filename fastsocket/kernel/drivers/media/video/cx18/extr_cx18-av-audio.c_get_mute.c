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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int cx18_av_read (struct cx18*,int) ; 

__attribute__((used)) static int get_mute(struct cx18 *cx)
{
	/* check SRC1_MUTE_EN */
	return cx18_av_read(cx, 0x8d3) & 0x2 ? 1 : 0;
}
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
struct inpcb {int /*<<< orphan*/  inp_nw_activity; } ;
typedef  int /*<<< orphan*/  activity_bitmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

inline void
inp_get_activity_bitmap(struct inpcb *inp, activity_bitmap_t *ab)
{
	bcopy(&inp->inp_nw_activity, ab, sizeof (*ab));
}
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
struct musb {int /*<<< orphan*/  (* board_set_vbus ) (struct musb*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct musb*,int) ; 

__attribute__((used)) static inline void musb_set_vbus(struct musb *musb, int is_on)
{
	musb->board_set_vbus(musb, is_on);
}
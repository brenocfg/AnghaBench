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
struct frame {int dummy; } ;
struct carlu {int /*<<< orphan*/  (* tx_fb_cb ) (struct carlu*,struct frame*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  carlu_free_frame (struct carlu*,struct frame*) ; 
 int /*<<< orphan*/  stub1 (struct carlu*,struct frame*) ; 

__attribute__((used)) static void carlu_tx_fb_cb(struct carlu *ar,
			      struct frame *frame)
{
	if (ar->tx_fb_cb)
		ar->tx_fb_cb(ar, frame);
	else
		carlu_free_frame(ar, frame);

}
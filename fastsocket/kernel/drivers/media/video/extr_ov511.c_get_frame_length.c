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
struct ov511_frame {int width; int height; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int get_depth (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline long int
get_frame_length(struct ov511_frame *frame)
{
	if (!frame)
		return 0;
	else
		return ((frame->width * frame->height
			 * get_depth(frame->format)) >> 3);
}
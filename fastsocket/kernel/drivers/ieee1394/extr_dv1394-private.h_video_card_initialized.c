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
struct video_card {scalar_t__ n_frames; } ;

/* Variables and functions */

__attribute__((used)) static inline int video_card_initialized(struct video_card *v)
{
	return v->n_frames > 0;
}
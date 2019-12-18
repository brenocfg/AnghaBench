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
struct video_data {int /*<<< orphan*/  urb_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_NUM ; 
 int /*<<< orphan*/  free_all_urb_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_all_urb(struct video_data *video)
{
	free_all_urb_generic(video->urb_array, SBUF_NUM);
}
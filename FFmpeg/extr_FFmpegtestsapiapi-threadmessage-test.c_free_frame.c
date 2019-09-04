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
struct message {scalar_t__ magic; int /*<<< orphan*/  frame; } ;

/* Variables and functions */
 scalar_t__ MAGIC ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_frame(void *arg)
{
    struct message *msg = arg;
    av_assert0(msg->magic == MAGIC);
    av_frame_free(&msg->frame);
}
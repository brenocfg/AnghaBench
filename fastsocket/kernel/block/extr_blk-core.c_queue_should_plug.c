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
struct request_queue {int dummy; } ;

/* Variables and functions */
 scalar_t__ blk_queue_nonrot (struct request_queue*) ; 
 scalar_t__ blk_queue_tagged (struct request_queue*) ; 

__attribute__((used)) static inline bool queue_should_plug(struct request_queue *q)
{
	return !(blk_queue_nonrot(q) && blk_queue_tagged(q));
}
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
struct kqueue {int dummy; } ;
typedef  int /*<<< orphan*/  kq_index_t ;

/* Variables and functions */
 int TAILQ_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqueue_get_queue (struct kqueue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kqueue_queue_empty(struct kqueue *kq, kq_index_t qos_index)
{
	return TAILQ_EMPTY(kqueue_get_queue(kq, qos_index));
}
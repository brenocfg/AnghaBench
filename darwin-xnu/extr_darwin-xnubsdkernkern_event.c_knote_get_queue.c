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
struct kqtailq {int dummy; } ;
struct knote {int /*<<< orphan*/  kn_qos_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  knote_get_kq (struct knote*) ; 
 struct kqtailq* kqueue_get_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kqtailq *
knote_get_queue(struct knote *kn)
{
	return kqueue_get_queue(knote_get_kq(kn), kn->kn_qos_index);
}
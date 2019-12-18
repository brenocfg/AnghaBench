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
struct kqworkq {struct kqrequest* kqwq_request; } ;
struct kqrequest {int dummy; } ;
typedef  size_t kq_index_t ;

/* Variables and functions */
 size_t KQWQ_NBUCKETS ; 
 int /*<<< orphan*/  assert (int) ; 

struct kqrequest *
kqworkq_get_request(struct kqworkq *kqwq, kq_index_t qos_index)
{
	assert(qos_index < KQWQ_NBUCKETS);
	return &kqwq->kqwq_request[qos_index];
}
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
struct kqrequest {int /*<<< orphan*/  kqr_override_index; int /*<<< orphan*/  kqr_qos_index; } ;
struct kqworkloop {struct kqrequest kqwl_request; } ;
typedef  int /*<<< orphan*/  kq_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kq_index_t
kqworkloop_owner_override(struct kqworkloop *kqwl)
{
	struct kqrequest *kqr = &kqwl->kqwl_request;
	return MAX(kqr->kqr_qos_index, kqr->kqr_override_index);
}
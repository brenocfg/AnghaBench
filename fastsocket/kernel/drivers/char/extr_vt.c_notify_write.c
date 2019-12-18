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
struct vt_notifier_param {unsigned int member_1; struct vc_data* vc; } ;
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VT_WRITE ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vt_notifier_param*) ; 
 int /*<<< orphan*/  vt_notifier_list ; 

__attribute__((used)) static void notify_write(struct vc_data *vc, unsigned int unicode)
{
	struct vt_notifier_param param = { .vc = vc, unicode = unicode };
	atomic_notifier_call_chain(&vt_notifier_list, VT_WRITE, &param);
}
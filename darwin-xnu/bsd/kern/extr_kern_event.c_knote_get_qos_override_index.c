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
struct knote {int /*<<< orphan*/  kn_qos_override; } ;
typedef  int /*<<< orphan*/  kq_index_t ;

/* Variables and functions */

__attribute__((used)) static kq_index_t
knote_get_qos_override_index(struct knote *kn)
{
	return kn->kn_qos_override;
}
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
struct o2hb_callback {int dummy; } ;
typedef  enum o2hb_callback_type { ____Placeholder_o2hb_callback_type } o2hb_callback_type ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct o2hb_callback* ERR_PTR (int /*<<< orphan*/ ) ; 
 int O2HB_NUM_CB ; 
 struct o2hb_callback* o2hb_callbacks ; 

__attribute__((used)) static struct o2hb_callback *hbcall_from_type(enum o2hb_callback_type type)
{
	if (type == O2HB_NUM_CB)
		return ERR_PTR(-EINVAL);

	return &o2hb_callbacks[type];
}
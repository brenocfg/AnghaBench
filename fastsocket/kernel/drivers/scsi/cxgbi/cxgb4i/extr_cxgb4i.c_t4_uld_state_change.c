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
struct cxgbi_device {int dummy; } ;
typedef  enum cxgb4_state { ____Placeholder_cxgb4_state } cxgb4_state ;

/* Variables and functions */
#define  CXGB4_STATE_DETACH 131 
#define  CXGB4_STATE_DOWN 130 
#define  CXGB4_STATE_START_RECOVERY 129 
#define  CXGB4_STATE_UP 128 
 int /*<<< orphan*/  cxgbi_device_unregister (struct cxgbi_device*) ; 
 int /*<<< orphan*/  pr_info (char*,struct cxgbi_device*,...) ; 

__attribute__((used)) static int t4_uld_state_change(void *handle, enum cxgb4_state state)
{
	struct cxgbi_device *cdev = handle;

	switch (state) {
	case CXGB4_STATE_UP:
		pr_info("cdev 0x%p, UP.\n", cdev);
		/* re-initialize */
		break;
	case CXGB4_STATE_START_RECOVERY:
		pr_info("cdev 0x%p, RECOVERY.\n", cdev);
		/* close all connections */
		break;
	case CXGB4_STATE_DOWN:
		pr_info("cdev 0x%p, DOWN.\n", cdev);
		break;
	case CXGB4_STATE_DETACH:
		pr_info("cdev 0x%p, DETACH.\n", cdev);
		cxgbi_device_unregister(cdev);
		break;
	default:
		pr_info("cdev 0x%p, unknown state %d.\n", cdev, state);
		break;
	}
	return 0;
}
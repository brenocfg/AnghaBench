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
typedef  int /*<<< orphan*/  user_size_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
struct coalition_resource_usage {int dummy; } ;
typedef  int kern_return_t ;
typedef  int /*<<< orphan*/  cru ;
typedef  int /*<<< orphan*/  coalition_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
#define  KERN_INVALID_ARGUMENT 130 
#define  KERN_RESOURCE_SHORTAGE 129 
#define  KERN_SUCCESS 128 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int) ; 
 int coalition_resource_usage_internal (int /*<<< orphan*/ ,struct coalition_resource_usage*) ; 
 int copyout (struct coalition_resource_usage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __attribute__ ((noinline))
coalition_info_resource_usage(coalition_t coal, user_addr_t buffer, user_size_t bufsize)
{
	kern_return_t kr;
	struct coalition_resource_usage cru = {};

	kr = coalition_resource_usage_internal(coal, &cru);

	switch (kr) {
	case KERN_INVALID_ARGUMENT:
		return EINVAL;
	case KERN_RESOURCE_SHORTAGE:
		return ENOMEM;
	case KERN_SUCCESS:
		break;
	default:
		return EIO; /* shrug */
	}

	return copyout(&cru, buffer, MIN(bufsize, sizeof(cru)));
}
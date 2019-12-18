#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  TYPE_1__* cap_user_header_t ;
typedef  int __u32 ;
struct TYPE_3__ {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  _KERNEL_CAPABILITY_VERSION ; 
 unsigned int _LINUX_CAPABILITY_U32S_1 ; 
 unsigned int _LINUX_CAPABILITY_U32S_3 ; 
#define  _LINUX_CAPABILITY_VERSION_1 130 
#define  _LINUX_CAPABILITY_VERSION_2 129 
#define  _LINUX_CAPABILITY_VERSION_3 128 
 scalar_t__ get_user (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn_deprecated_v2 () ; 
 int /*<<< orphan*/  warn_legacy_capability_use () ; 

__attribute__((used)) static int cap_validate_magic(cap_user_header_t header, unsigned *tocopy)
{
	__u32 version;

	if (get_user(version, &header->version))
		return -EFAULT;

	switch (version) {
	case _LINUX_CAPABILITY_VERSION_1:
		warn_legacy_capability_use();
		*tocopy = _LINUX_CAPABILITY_U32S_1;
		break;
	case _LINUX_CAPABILITY_VERSION_2:
		warn_deprecated_v2();
		/*
		 * fall through - v3 is otherwise equivalent to v2.
		 */
	case _LINUX_CAPABILITY_VERSION_3:
		*tocopy = _LINUX_CAPABILITY_U32S_3;
		break;
	default:
		if (put_user((u32)_KERNEL_CAPABILITY_VERSION, &header->version))
			return -EFAULT;
		return -EINVAL;
	}

	return 0;
}
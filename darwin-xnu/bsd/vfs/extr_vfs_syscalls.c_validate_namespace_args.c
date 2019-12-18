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
typedef  int /*<<< orphan*/  user64_namespace_handler_info_ext ;
typedef  int /*<<< orphan*/  user64_namespace_handler_info ;
typedef  int /*<<< orphan*/  user64_namespace_handler_data ;
typedef  int /*<<< orphan*/  user32_namespace_handler_info_ext ;
typedef  int /*<<< orphan*/  user32_namespace_handler_info ;
typedef  int /*<<< orphan*/  user32_namespace_handler_data ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int validate_namespace_args (int is64bit, int size) {

	if (is64bit) {
		/* Must be one of these */
		if (size == sizeof(user64_namespace_handler_info)) {
			goto sizeok;
		}
		if (size == sizeof(user64_namespace_handler_info_ext)) {
			goto sizeok;
		}
		if (size == sizeof(user64_namespace_handler_data)) {
			goto sizeok;
		}
		return EINVAL;
	}
	else {
		/* 32 bit -- must be one of these */
		if (size == sizeof(user32_namespace_handler_info)) {
			goto sizeok;
		}
		if (size == sizeof(user32_namespace_handler_info_ext)) {
			goto sizeok;
		}
		if (size == sizeof(user32_namespace_handler_data)) {
			goto sizeok;
		}
		return EINVAL;
	}

sizeok:

	return 0;

}
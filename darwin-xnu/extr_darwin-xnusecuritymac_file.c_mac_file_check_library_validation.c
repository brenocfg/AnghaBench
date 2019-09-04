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
typedef  int /*<<< orphan*/  user_long_t ;
struct proc {int dummy; } ;
struct fileglob {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct proc*,struct fileglob*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  file_check_library_validation ; 

int
mac_file_check_library_validation(struct proc *proc,
	struct fileglob *fg, off_t slice_offset,
	user_long_t error_message, size_t error_message_size)
{
	int error;

	MAC_CHECK(file_check_library_validation, proc, fg, slice_offset, error_message, error_message_size);
	return (error);
}
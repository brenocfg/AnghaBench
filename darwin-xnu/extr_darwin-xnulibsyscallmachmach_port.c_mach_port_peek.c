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
typedef  int /*<<< orphan*/  mach_port_seqno_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_msg_trailer_type_t ;
typedef  int /*<<< orphan*/  mach_msg_trailer_info_t ;
typedef  int /*<<< orphan*/  mach_msg_size_t ;
typedef  int /*<<< orphan*/  mach_msg_id_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;

/* Variables and functions */
 int /*<<< orphan*/  _kernelrpc_mach_port_peek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
mach_port_peek(
	ipc_space_t		task,
	mach_port_name_t	name,
	mach_msg_trailer_type_t trailer_type,
	mach_port_seqno_t	*seqnop,
	mach_msg_size_t		*msg_sizep,
	mach_msg_id_t		*msg_idp,
	mach_msg_trailer_info_t trailer_infop,
	mach_msg_type_number_t	*trailer_sizep)
{
	kern_return_t rv;

	rv = _kernelrpc_mach_port_peek(task, name, trailer_type, 
				       seqnop, msg_sizep, msg_idp,
				       trailer_infop, trailer_sizep);

	return (rv);
}
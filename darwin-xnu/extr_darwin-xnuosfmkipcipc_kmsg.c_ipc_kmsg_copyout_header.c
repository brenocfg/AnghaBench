#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ mach_msg_type_name_t ;
typedef  int mach_msg_return_t ;
typedef  int mach_msg_option_t ;
struct TYPE_22__ {int /*<<< orphan*/  msgh_voucher_port; void* msgh_remote_port; TYPE_2__* msgh_local_port; scalar_t__ msgh_bits; scalar_t__ msgh_id; } ;
typedef  TYPE_1__ mach_msg_header_t ;
typedef  scalar_t__ mach_msg_bits_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_port_timestamp_t ;
typedef  TYPE_2__* ipc_port_t ;
typedef  void* ipc_object_t ;
typedef  TYPE_3__* ipc_kmsg_t ;
typedef  TYPE_4__* ipc_entry_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_25__ {int ie_bits; scalar_t__ ie_object; } ;
struct TYPE_24__ {TYPE_1__* ikm_header; TYPE_2__* ikm_voucher; } ;
struct TYPE_23__ {int /*<<< orphan*/  ip_timestamp; } ;

/* Variables and functions */
 void* CAST_MACH_NAME_TO_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAST_MACH_PORT_TO_NAME (TYPE_2__*) ; 
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_IPC ; 
 scalar_t__ FALSE ; 
 scalar_t__ IE_BITS_TYPE (int) ; 
 scalar_t__ IKOT_VOUCHER ; 
 scalar_t__ IO_NULL ; 
 TYPE_2__* IP_DEAD ; 
 void* IP_NULL ; 
 scalar_t__ IP_TIMESTAMP_ORDER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IP_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  ITS_SIZE_NONE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,uintptr_t,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_IPC_MSG_RECV ; 
 int /*<<< orphan*/  MACH_IPC_MSG_RECV_VOUCHER_REFUSED ; 
 scalar_t__ MACH_MSGH_BITS_LOCAL (scalar_t__) ; 
 scalar_t__ MACH_MSGH_BITS_REMOTE (scalar_t__) ; 
 scalar_t__ MACH_MSGH_BITS_SET (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ MACH_MSGH_BITS_VOUCHER (scalar_t__) ; 
 scalar_t__ MACH_MSGH_BITS_ZERO ; 
 int MACH_MSG_IPC_SPACE ; 
 int MACH_MSG_SUCCESS ; 
 scalar_t__ MACH_MSG_TYPE_MOVE_SEND ; 
 scalar_t__ MACH_MSG_TYPE_PORT_SEND_ONCE ; 
 int /*<<< orphan*/  MACH_PORT_DEAD ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 scalar_t__ MACH_PORT_TYPE_NONE ; 
 int MACH_PORT_TYPE_SEND ; 
 int MACH_PORT_TYPE_SEND_RECEIVE ; 
 int MACH_RCV_HEADER_ERROR ; 
 int MACH_RCV_VOUCHER ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRPERM (uintptr_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (TYPE_2__*) ; 
 scalar_t__ ip_kotype (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_release (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_entries_hold (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ipc_entry_claim (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__**) ; 
 int /*<<< orphan*/  ipc_entry_grow_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_object_copyout_dest (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_port_release_send (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_port_release_sonce (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_port_spnotify (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_right_copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,scalar_t__,void*) ; 
 scalar_t__ ipc_right_reverse (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,TYPE_4__**) ; 
 int /*<<< orphan*/  is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_read_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_write_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ unsafe_convert_port_to_voucher (TYPE_2__*) ; 

mach_msg_return_t
ipc_kmsg_copyout_header(
	ipc_kmsg_t              kmsg,
	ipc_space_t		space,
	mach_msg_option_t	option)
{
	mach_msg_header_t *msg = kmsg->ikm_header;
	mach_msg_bits_t mbits = msg->msgh_bits;
	ipc_port_t dest = (ipc_port_t) msg->msgh_remote_port;

	assert(IP_VALID(dest));

	/*
	 * While we still hold a reference on the received-from port,
	 * process all send-possible notfications we received along with
	 * the message.
	 */
	ipc_port_spnotify(dest);

    {
	mach_msg_type_name_t dest_type = MACH_MSGH_BITS_REMOTE(mbits);
	mach_msg_type_name_t reply_type = MACH_MSGH_BITS_LOCAL(mbits);
	mach_msg_type_name_t voucher_type = MACH_MSGH_BITS_VOUCHER(mbits);
	ipc_port_t reply = msg->msgh_local_port;
	ipc_port_t release_reply_port = IP_NULL;
	mach_port_name_t dest_name, reply_name;

	ipc_port_t voucher = kmsg->ikm_voucher;
	ipc_port_t release_voucher_port = IP_NULL;
	mach_port_name_t voucher_name;

	uint32_t entries_held = 0;
	boolean_t need_write_lock = FALSE;
	kern_return_t kr;

	/*
	 * Reserve any potentially needed entries in the target space.
	 * We'll free any unused before unlocking the space.
	 */
	if (IP_VALID(reply)) {
		entries_held++;
		need_write_lock = TRUE;
	}
	if (IP_VALID(voucher)) {
		assert(voucher_type == MACH_MSG_TYPE_MOVE_SEND); 

		if ((option & MACH_RCV_VOUCHER) != 0)
 			entries_held++;
		need_write_lock = TRUE;
	}

	if (need_write_lock) {

		is_write_lock(space);

		while(entries_held) {
			if (!is_active(space)) {
				is_write_unlock(space);
				return (MACH_RCV_HEADER_ERROR|
					MACH_MSG_IPC_SPACE);
			}
				
			kr = ipc_entries_hold(space, entries_held);
			if (KERN_SUCCESS == kr)
				break;

			kr = ipc_entry_grow_table(space, ITS_SIZE_NONE);
			if (KERN_SUCCESS != kr)
				return(MACH_RCV_HEADER_ERROR|
				       MACH_MSG_IPC_SPACE);
			/* space was unlocked and relocked - retry */
		}

		/* Handle reply port. */
		if (IP_VALID(reply)) {
			ipc_entry_t entry;

			/* Is there already an entry we can use? */
			if ((reply_type != MACH_MSG_TYPE_PORT_SEND_ONCE) &&
			    ipc_right_reverse(space, (ipc_object_t) reply, &reply_name, &entry)) {
				/* reply port is locked and active */
				assert(entry->ie_bits & MACH_PORT_TYPE_SEND_RECEIVE);
			} else {
				ip_lock(reply);
				if (!ip_active(reply)) {
					ip_unlock(reply);
					
					release_reply_port = reply;
					reply = IP_DEAD;
					reply_name = MACH_PORT_DEAD;
					goto done_with_reply;
				}
				
				/* claim a held entry for the reply port */
				assert(entries_held > 0);
				entries_held--;
				ipc_entry_claim(space, &reply_name, &entry);
				assert(IE_BITS_TYPE(entry->ie_bits) == MACH_PORT_TYPE_NONE);
				assert(entry->ie_object == IO_NULL); 
				entry->ie_object = (ipc_object_t) reply;
			}

			/* space and reply port are locked and active */
			ip_reference(reply);	/* hold onto the reply port */

			kr = ipc_right_copyout(space, reply_name, entry,
					       reply_type, TRUE, (ipc_object_t) reply);
			assert(kr == KERN_SUCCESS);
			/* reply port is unlocked */
		} else
			reply_name = CAST_MACH_PORT_TO_NAME(reply);

	done_with_reply:

		/* Handle voucher port. */
		if (voucher_type != MACH_MSGH_BITS_ZERO) {
			assert(voucher_type == MACH_MSG_TYPE_MOVE_SEND);

			if (!IP_VALID(voucher)) {
				if ((option & MACH_RCV_VOUCHER) == 0) {
					voucher_type = MACH_MSGH_BITS_ZERO;
				}
				voucher_name = MACH_PORT_NULL;
				goto done_with_voucher;
			}
			
			/* clear voucher from its hiding place back in the kmsg */
			kmsg->ikm_voucher = IP_NULL;

			if ((option & MACH_RCV_VOUCHER) != 0) {
				ipc_entry_t entry;

				if (ipc_right_reverse(space, (ipc_object_t) voucher,
						      &voucher_name, &entry)) {
					/* voucher port locked */
					assert(entry->ie_bits & MACH_PORT_TYPE_SEND);
				} else {
					assert(entries_held > 0);
					entries_held--;
					ipc_entry_claim(space, &voucher_name, &entry);
					assert(IE_BITS_TYPE(entry->ie_bits) == MACH_PORT_TYPE_NONE);
					assert(entry->ie_object == IO_NULL); 
					entry->ie_object = (ipc_object_t) voucher;
					ip_lock(voucher);
				}
				/* space is locked and active */

				assert(ip_active(voucher));
				assert(ip_kotype(voucher) == IKOT_VOUCHER);
				kr = ipc_right_copyout(space, voucher_name, entry,
						       MACH_MSG_TYPE_MOVE_SEND, TRUE, 
						       (ipc_object_t) voucher);
				/* voucher port is unlocked */
			} else {
				voucher_type = MACH_MSGH_BITS_ZERO;
				release_voucher_port = voucher;
				voucher_name = MACH_PORT_NULL;
			}
		} else {
			voucher_name = msg->msgh_voucher_port;
		}

	done_with_voucher:

		ip_lock(dest);
		is_write_unlock(space);

	} else {
		/*
		 *	No reply or voucher port!  This is an easy case.
		 *	We only need to have the space locked
		 *	when locking the destination.
		 */

		is_read_lock(space);
		if (!is_active(space)) {
			is_read_unlock(space);
			return MACH_RCV_HEADER_ERROR|MACH_MSG_IPC_SPACE;
		}

		ip_lock(dest);
		is_read_unlock(space);

		reply_name = CAST_MACH_PORT_TO_NAME(reply);

		if (voucher_type != MACH_MSGH_BITS_ZERO) {
			assert(voucher_type == MACH_MSG_TYPE_MOVE_SEND);
			if ((option & MACH_RCV_VOUCHER) == 0) {
				voucher_type = MACH_MSGH_BITS_ZERO;
			}
			voucher_name = MACH_PORT_NULL;
		} else {
			voucher_name = msg->msgh_voucher_port;
		}
	}

	/*
	 *	At this point, the space is unlocked and the destination
	 *	port is locked.  (Lock taken while space was locked.)
	 *	reply_name is taken care of; we still need dest_name.
	 *	We still hold a ref for reply (if it is valid).
	 *
	 *	If the space holds receive rights for the destination,
	 *	we return its name for the right.  Otherwise the task
	 *	managed to destroy or give away the receive right between
	 *	receiving the message and this copyout.  If the destination
	 *	is dead, return MACH_PORT_DEAD, and if the receive right
	 *	exists somewhere else (another space, in transit)
	 *	return MACH_PORT_NULL.
	 *
	 *	Making this copyout operation atomic with the previous
	 *	copyout of the reply port is a bit tricky.  If there was
	 *	no real reply port (it wasn't IP_VALID) then this isn't
	 *	an issue.  If the reply port was dead at copyout time,
	 *	then we are OK, because if dest is dead we serialize
	 *	after the death of both ports and if dest is alive
	 *	we serialize after reply died but before dest's (later) death.
	 *	So assume reply was alive when we copied it out.  If dest
	 *	is alive, then we are OK because we serialize before
	 *	the ports' deaths.  So assume dest is dead when we look at it.
	 *	If reply dies/died after dest, then we are OK because
	 *	we serialize after dest died but before reply dies.
	 *	So the hard case is when reply is alive at copyout,
	 *	dest is dead at copyout, and reply died before dest died.
	 *	In this case pretend that dest is still alive, so
	 *	we serialize while both ports are alive.
	 *
	 *	Because the space lock is held across the copyout of reply
	 *	and locking dest, the receive right for dest can't move
	 *	in or out of the space while the copyouts happen, so
	 *	that isn't an atomicity problem.  In the last hard case
	 *	above, this implies that when dest is dead that the
	 *	space couldn't have had receive rights for dest at
	 *	the time reply was copied-out, so when we pretend
	 *	that dest is still alive, we can return MACH_PORT_NULL.
	 *
	 *	If dest == reply, then we have to make it look like
	 *	either both copyouts happened before the port died,
	 *	or both happened after the port died.  This special
	 *	case works naturally if the timestamp comparison
	 *	is done correctly.
	 */

	if (ip_active(dest)) {
		ipc_object_copyout_dest(space, (ipc_object_t) dest,
					dest_type, &dest_name);
		/* dest is unlocked */

	} else {
		ipc_port_timestamp_t timestamp;

		timestamp = dest->ip_timestamp;
		ip_unlock(dest);
		ip_release(dest);

		if (IP_VALID(reply)) {
			ip_lock(reply);
			if (ip_active(reply) ||
			    IP_TIMESTAMP_ORDER(timestamp,
					       reply->ip_timestamp))
				dest_name = MACH_PORT_DEAD;
			else
				dest_name = MACH_PORT_NULL;
			ip_unlock(reply);
		} else
			dest_name = MACH_PORT_DEAD;
	}

	if (IP_VALID(reply))
		ip_release(reply);

	if (IP_VALID(release_reply_port)) {
		if (reply_type == MACH_MSG_TYPE_PORT_SEND_ONCE)
			ipc_port_release_sonce(release_reply_port);
		else
			ipc_port_release_send(release_reply_port);
	}

	if (IP_VALID(release_voucher_port))
		ipc_port_release_send(release_voucher_port);


	if ((option & MACH_RCV_VOUCHER) != 0) {
	    KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_IPC, MACH_IPC_MSG_RECV) | DBG_FUNC_NONE,
				  VM_KERNEL_ADDRPERM((uintptr_t)kmsg),
				  (uintptr_t)kmsg->ikm_header->msgh_bits,
				  (uintptr_t)kmsg->ikm_header->msgh_id,
				  VM_KERNEL_ADDRPERM((uintptr_t)unsafe_convert_port_to_voucher(voucher)),
				  0);
	} else {
	    KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_IPC, MACH_IPC_MSG_RECV_VOUCHER_REFUSED) | DBG_FUNC_NONE,
				  VM_KERNEL_ADDRPERM((uintptr_t)kmsg),
				  (uintptr_t)kmsg->ikm_header->msgh_bits,
				  (uintptr_t)kmsg->ikm_header->msgh_id,
				  VM_KERNEL_ADDRPERM((uintptr_t)unsafe_convert_port_to_voucher(voucher)),
				  0);
	}

	msg->msgh_bits = MACH_MSGH_BITS_SET(reply_type, dest_type,
					    voucher_type, mbits);
	msg->msgh_local_port = CAST_MACH_NAME_TO_PORT(dest_name);
	msg->msgh_remote_port = CAST_MACH_NAME_TO_PORT(reply_name);
	msg->msgh_voucher_port = voucher_name;
    }

    return MACH_MSG_SUCCESS;
}
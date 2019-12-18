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
struct proto_input_entry {scalar_t__ protocol; void* inject_last; int /*<<< orphan*/ * inject_first; struct proto_input_entry* next; } ;
struct dlil_threading_info {int input_waiting; int /*<<< orphan*/  input_lck; } ;
typedef  scalar_t__ protocol_family_t ;
typedef  void* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int DLIL_INPUT_RUNNING ; 
 int DLIL_PROTO_WAITING ; 
 int /*<<< orphan*/  ENOENT ; 
 struct dlil_threading_info* dlil_main_input_thread ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbuf_nextpkt (void*) ; 
 int /*<<< orphan*/  mbuf_setnextpkt (void*,void*) ; 
 struct proto_input_entry** proto_hash ; 
 int proto_hash_value (scalar_t__) ; 
 int /*<<< orphan*/  proto_total_waiting ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

errno_t
proto_inject(protocol_family_t protocol, mbuf_t packet_list)
{
	struct proto_input_entry *entry;
	mbuf_t last_packet;
	int hash_slot = proto_hash_value(protocol);
	struct dlil_threading_info *inp = dlil_main_input_thread;

	for (last_packet = packet_list; mbuf_nextpkt(last_packet) != NULL;
	    last_packet = mbuf_nextpkt(last_packet))
		/* find the last packet */;

	for (entry = proto_hash[hash_slot]; entry != NULL;
	    entry = entry->next) {
		if (entry->protocol == protocol)
			break;
	}

	if (entry != NULL) {
		lck_mtx_lock(&inp->input_lck);
		if (entry->inject_first == NULL) {
			proto_total_waiting++;
			inp->input_waiting |= DLIL_PROTO_WAITING;
			entry->inject_first = packet_list;
		} else {
			mbuf_setnextpkt(entry->inject_last, packet_list);
		}
		entry->inject_last = last_packet;
		if ((inp->input_waiting & DLIL_INPUT_RUNNING) == 0) {
			wakeup((caddr_t)&inp->input_waiting);
		}
		lck_mtx_unlock(&inp->input_lck);
	} else {
		return (ENOENT);
	}

	return (0);
}
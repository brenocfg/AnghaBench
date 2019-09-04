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
struct TYPE_3__ {unsigned char const* _msg; unsigned char const* _eom; unsigned char const** _sections; int _sect; int _rrnum; int /*<<< orphan*/ * _msg_ptr; scalar_t__* _counts; scalar_t__ _flags; scalar_t__ _id; } ;
typedef  TYPE_1__ ns_msg ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  NS_GET16 (scalar_t__,unsigned char const*) ; 
 int NS_INT16SZ ; 
 int /*<<< orphan*/  errno ; 
 int ns_s_max ; 
 int ns_skiprr (unsigned char const*,unsigned char const*,int,scalar_t__) ; 

int ns_initparse(const unsigned char *msg, int msglen, ns_msg *handle)
{
	int i, r;

	handle->_msg = msg;
	handle->_eom = msg + msglen;
	if (msglen < (2 + ns_s_max) * NS_INT16SZ) goto bad;
	NS_GET16(handle->_id, msg);
	NS_GET16(handle->_flags, msg);
	for (i = 0; i < ns_s_max; i++) NS_GET16(handle->_counts[i], msg);
	for (i = 0; i < ns_s_max; i++) {
		if (handle->_counts[i]) {
			handle->_sections[i] = msg;
			r = ns_skiprr(msg, handle->_eom, i, handle->_counts[i]);
			if (r < 0) return -1;
			msg += r;
		} else {
			handle->_sections[i] = NULL;
		}
	}
	if (msg != handle->_eom) goto bad;
	handle->_sect = ns_s_max;
	handle->_rrnum = -1;
	handle->_msg_ptr = NULL;
	return 0;
bad:
	errno = EMSGSIZE;
	return -1;
}
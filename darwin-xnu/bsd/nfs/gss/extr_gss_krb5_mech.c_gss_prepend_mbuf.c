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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_WAITOK ; 
 int /*<<< orphan*/ * mbuf_data (int /*<<< orphan*/ ) ; 
 size_t mbuf_leadingspace (int /*<<< orphan*/ ) ; 
 size_t mbuf_len (int /*<<< orphan*/ ) ; 
 scalar_t__ mbuf_prepend (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_setdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t mbuf_trailingspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

errno_t
gss_prepend_mbuf(mbuf_t *chain, uint8_t *bytes, size_t size)
{
	uint8_t *data = mbuf_data(*chain);
	size_t leading = mbuf_leadingspace(*chain);
	size_t trailing = mbuf_trailingspace(*chain);
	size_t mlen = mbuf_len(*chain);
	errno_t error;

	if (size > leading && size <= leading + trailing) {
		data = memmove(data + size - leading, data, mlen);
		mbuf_setdata(*chain, data, mlen);
	}

	error = mbuf_prepend(chain, size, MBUF_WAITOK);
	if (error)
		return (error);
	data = mbuf_data(*chain);
	memcpy(data, bytes, size);

	return (0);
}
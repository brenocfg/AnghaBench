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
typedef  int u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct sockbuf {scalar_t__ sb_hiwat; } ;

/* Variables and functions */
 int MCLSHIFT ; 
 int MSIZESHIFT ; 
 int /*<<< orphan*/  OSIncrementAtomic64 (int /*<<< orphan*/ *) ; 
 int nmbclusters ; 
 int /*<<< orphan*/  sbmb_limreached ; 
 scalar_t__ total_sbmb_cnt ; 

u_int8_t
tcp_cansbgrow(struct sockbuf *sb)
{
	/* Calculate the host level space limit in terms of MSIZE buffers.
	 * We can use a maximum of half of the available mbuf space for
	 * socket buffers.
	 */
	u_int32_t mblim = ((nmbclusters >> 1) << (MCLSHIFT - MSIZESHIFT));

	/* Calculate per sb limit in terms of bytes. We optimize this limit
	 * for upto 16 socket buffers.
	 */

	u_int32_t sbspacelim = ((nmbclusters >> 4) << MCLSHIFT);

	if ((total_sbmb_cnt < mblim) &&
		(sb->sb_hiwat < sbspacelim)) {
		return(1);
	} else {
		OSIncrementAtomic64(&sbmb_limreached);
	}
	return(0);
}
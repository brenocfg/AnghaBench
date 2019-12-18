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
typedef  int __u8 ;
typedef  unsigned int __u32 ;

/* Variables and functions */
 unsigned int MAX_TCP_WINDOW ; 
 int TCP_DEFAULT_INIT_RCVWND ; 
 void* max_t (int /*<<< orphan*/ ,int,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int sysctl_rmem_max ; 
 int* sysctl_tcp_rmem ; 
 scalar_t__ sysctl_tcp_workaround_signed_windows ; 
 int /*<<< orphan*/  u32 ; 

void tcp_select_initial_window(int __space, __u32 mss,
			       __u32 *rcv_wnd, __u32 *window_clamp,
			       int wscale_ok, __u8 *rcv_wscale,
			       __u32 init_rcv_wnd)
{
	unsigned int space = (__space < 0 ? 0 : __space);

	/* If no clamp set the clamp to the max possible scaled window */
	if (*window_clamp == 0)
		(*window_clamp) = (65535 << 14);
	space = min(*window_clamp, space);

	/* Quantize space offering to a multiple of mss if possible. */
	if (space > mss)
		space = (space / mss) * mss;

	/* NOTE: offering an initial window larger than 32767
	 * will break some buggy TCP stacks. If the admin tells us
	 * it is likely we could be speaking with such a buggy stack
	 * we will truncate our initial window offering to 32K-1
	 * unless the remote has sent us a window scaling option,
	 * which we interpret as a sign the remote TCP is not
	 * misinterpreting the window field as a signed quantity.
	 */
	if (sysctl_tcp_workaround_signed_windows)
		(*rcv_wnd) = min(space, MAX_TCP_WINDOW);
	else
		(*rcv_wnd) = space;

	(*rcv_wscale) = 0;
	if (wscale_ok) {
		/* Set window scaling on max possible window
		 * See RFC1323 for an explanation of the limit to 14
		 */
		space = max_t(u32, sysctl_tcp_rmem[2], sysctl_rmem_max);
		space = min_t(u32, space, *window_clamp);
		while (space > 65535 && (*rcv_wscale) < 14) {
			space >>= 1;
			(*rcv_wscale)++;
		}
	}

	/* Set initial window to a value enough for senders starting with
	 * initial congestion window of TCP_DEFAULT_INIT_RCVWND. Place
	 * a limit on the initial window when mss is larger than 1460.
	 */
	if (mss > (1 << *rcv_wscale)) {
		int init_cwnd = TCP_DEFAULT_INIT_RCVWND;
		if (mss > 1460)
			init_cwnd =
			max_t(u32, (1460 * TCP_DEFAULT_INIT_RCVWND) / mss, 2);
		/* when initializing use the value from init_rcv_wnd
		 * rather than the default from above
		 */
		if (init_rcv_wnd)
			*rcv_wnd = min(*rcv_wnd, init_rcv_wnd * mss);
		else
			*rcv_wnd = min(*rcv_wnd, init_cwnd * mss);
	}

	/* Set the clamp no higher than max representable value */
	(*window_clamp) = min(65535U << (*rcv_wscale), *window_clamp);
}
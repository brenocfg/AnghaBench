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
typedef  int u32 ;
struct request_sock {int dummy; } ;
struct inet_request_sock {int snd_wscale; int rcv_wscale; int sack_ok; scalar_t__ wscale_ok; } ;
typedef  int __u32 ;

/* Variables and functions */
 int TSBITS ; 
 int TSMASK ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 int tcp_time_stamp ; 

__u32 cookie_init_timestamp(struct request_sock *req)
{
	struct inet_request_sock *ireq;
	u32 ts, ts_now = tcp_time_stamp;
	u32 options = 0;

	ireq = inet_rsk(req);
	if (ireq->wscale_ok) {
		options = ireq->snd_wscale;
		options |= ireq->rcv_wscale << 4;
	}
	options |= ireq->sack_ok << 8;

	ts = ts_now & ~TSMASK;
	ts |= options;
	if (ts > ts_now) {
		ts >>= TSBITS;
		ts--;
		ts <<= TSBITS;
		ts |= options;
	}
	return ts;
}
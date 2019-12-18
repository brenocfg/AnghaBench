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
struct usb_host_endpoint {int dummy; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  wMaxPacketSize; } ;
struct urb {int dummy; } ;
struct r8a66597_pipe_info {scalar_t__ type; int dir_in; scalar_t__ timer_interval; scalar_t__ interval; int /*<<< orphan*/  pipenum; int /*<<< orphan*/  buf_bsize; int /*<<< orphan*/  bufnum; int /*<<< orphan*/  maxpacket; int /*<<< orphan*/  epnum; int /*<<< orphan*/  address; } ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 scalar_t__ R8A66597_BULK ; 
 int /*<<< orphan*/  enable_r8a66597_pipe (struct r8a66597*,struct urb*,struct usb_host_endpoint*,struct r8a66597_pipe_info*) ; 
 int /*<<< orphan*/  get_buf_bsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bufnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_empty_pipenum (struct r8a66597*,struct usb_endpoint_descriptor*) ; 
 scalar_t__ get_interval (struct urb*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_r8a66597_type (int /*<<< orphan*/ ) ; 
 scalar_t__ get_timer_interval (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_urb_to_r8a66597_addr (struct r8a66597*,struct urb*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_dir_in (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_endpoint_num (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_endpoint_type (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static void init_pipe_info(struct r8a66597 *r8a66597, struct urb *urb,
			   struct usb_host_endpoint *hep,
			   struct usb_endpoint_descriptor *ep)
{
	struct r8a66597_pipe_info info;

	info.pipenum = get_empty_pipenum(r8a66597, ep);
	info.address = get_urb_to_r8a66597_addr(r8a66597, urb);
	info.epnum = usb_endpoint_num(ep);
	info.maxpacket = le16_to_cpu(ep->wMaxPacketSize);
	info.type = get_r8a66597_type(usb_endpoint_type(ep));
	info.bufnum = get_bufnum(info.pipenum);
	info.buf_bsize = get_buf_bsize(info.pipenum);
	if (info.type == R8A66597_BULK) {
		info.interval = 0;
		info.timer_interval = 0;
	} else {
		info.interval = get_interval(urb, ep->bInterval);
		info.timer_interval = get_timer_interval(urb, ep->bInterval);
	}
	if (usb_endpoint_dir_in(ep))
		info.dir_in = 1;
	else
		info.dir_in = 0;

	enable_r8a66597_pipe(r8a66597, urb, hep, &info);
}
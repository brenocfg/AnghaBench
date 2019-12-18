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
struct vhost_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHOST_NET_VQ_RX ; 
 int /*<<< orphan*/  VHOST_NET_VQ_TX ; 
 int /*<<< orphan*/  vhost_net_flush_vq (struct vhost_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vhost_net_flush(struct vhost_net *n)
{
	vhost_net_flush_vq(n, VHOST_NET_VQ_TX);
	vhost_net_flush_vq(n, VHOST_NET_VQ_RX);
}
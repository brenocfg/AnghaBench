#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_5__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_10__ {int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct TYPE_11__ {TYPE_3__ addr; } ;
struct rdma_cm_id {TYPE_4__ route; } ;
struct TYPE_13__ {int /*<<< orphan*/  addr; } ;
struct TYPE_14__ {TYPE_6__ ip4; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {TYPE_1__ ip4; } ;
struct cma_hdr {int /*<<< orphan*/  port; TYPE_7__ src_addr; TYPE_2__ dst_addr; } ;

/* Variables and functions */

__attribute__((used)) static void cma_save_ip4_info(struct rdma_cm_id *id, struct rdma_cm_id *listen_id,
			      struct cma_hdr *hdr)
{
	struct sockaddr_in *listen4, *ip4;

	listen4 = (struct sockaddr_in *) &listen_id->route.addr.src_addr;
	ip4 = (struct sockaddr_in *) &id->route.addr.src_addr;
	ip4->sin_family = listen4->sin_family;
	ip4->sin_addr.s_addr = hdr->dst_addr.ip4.addr;
	ip4->sin_port = listen4->sin_port;

	ip4 = (struct sockaddr_in *) &id->route.addr.dst_addr;
	ip4->sin_family = listen4->sin_family;
	ip4->sin_addr.s_addr = hdr->src_addr.ip4.addr;
	ip4->sin_port = hdr->port;
}
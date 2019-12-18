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
struct vio_rdx {int /*<<< orphan*/  tag; } ;
struct vio_driver_state {int dummy; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int /*<<< orphan*/  VIO_RDX ; 
 int /*<<< orphan*/  VIO_SUBTYPE_INFO ; 
 int /*<<< orphan*/  VIO_TYPE_CTRL ; 
 int /*<<< orphan*/  init_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct vio_rdx*,int /*<<< orphan*/ ,int) ; 
 int send_ctrl (struct vio_driver_state*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int send_rdx(struct vio_driver_state *vio)
{
	struct vio_rdx pkt;

	memset(&pkt, 0, sizeof(pkt));

	init_tag(&pkt.tag, VIO_TYPE_CTRL, VIO_SUBTYPE_INFO, VIO_RDX);

	viodbg(HS, "SEND RDX INFO\n");

	return send_ctrl(vio, &pkt.tag, sizeof(pkt));
}
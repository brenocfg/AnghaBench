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
struct scatterlist {int /*<<< orphan*/  length; } ;
struct qdio_buffer_element {int /*<<< orphan*/  eflags; int /*<<< orphan*/  length; void* addr; int /*<<< orphan*/  sflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBAL_EFLAGS_LAST_ENTRY ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_TYPE_WRITE_READ ; 
 void* sg_virt (struct scatterlist*) ; 

__attribute__((used)) static void zfcp_fsf_setup_ct_els_unchained(struct qdio_buffer_element *sbale,
					    struct scatterlist *sg_req,
					    struct scatterlist *sg_resp)
{
	sbale[0].sflags |= SBAL_SFLAGS0_TYPE_WRITE_READ;
	sbale[2].addr   = sg_virt(sg_req);
	sbale[2].length = sg_req->length;
	sbale[3].addr   = sg_virt(sg_resp);
	sbale[3].length = sg_resp->length;
	sbale[3].eflags |= SBAL_EFLAGS_LAST_ENTRY;
}
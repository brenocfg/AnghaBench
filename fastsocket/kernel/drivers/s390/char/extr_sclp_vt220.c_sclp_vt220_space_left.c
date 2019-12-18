#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; } ;
struct sclp_vt220_sccb {TYPE_2__ header; } ;
struct TYPE_3__ {scalar_t__ sccb; } ;
struct sclp_vt220_request {TYPE_1__ sclp_req; } ;

/* Variables and functions */
 int PAGE_SIZE ; 

__attribute__((used)) static inline unsigned int
sclp_vt220_space_left(struct sclp_vt220_request *request)
{
	struct sclp_vt220_sccb *sccb;
	sccb = (struct sclp_vt220_sccb *) request->sclp_req.sccb;
	return PAGE_SIZE - sizeof(struct sclp_vt220_request) -
	       sccb->header.length;
}
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
struct carm_host {scalar_t__ msg_dma; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 unsigned int CARM_MSG_SIZE ; 

__attribute__((used)) static inline dma_addr_t carm_ref_msg_dma(struct carm_host *host,
					  unsigned int msg_idx)
{
	return host->msg_dma + (msg_idx * CARM_MSG_SIZE);
}
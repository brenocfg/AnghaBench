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
typedef  int u16 ;
struct MPT3SAS_ADAPTER {int request_sz; scalar_t__ request; } ;

/* Variables and functions */

void *
mpt3sas_base_get_msg_frame(struct MPT3SAS_ADAPTER *ioc, u16 smid)
{
	return (void *)(ioc->request + (smid * ioc->request_sz));
}
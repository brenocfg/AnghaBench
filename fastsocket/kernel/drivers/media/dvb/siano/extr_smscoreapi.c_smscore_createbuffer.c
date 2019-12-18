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
typedef  int /*<<< orphan*/  u8 ;
struct smscore_buffer_t {int offset_in_common; scalar_t__ phys; int /*<<< orphan*/ * p; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct smscore_buffer_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_info (char*) ; 

__attribute__((used)) static struct
smscore_buffer_t *smscore_createbuffer(u8 *buffer, void *common_buffer,
				       dma_addr_t common_buffer_phys)
{
	struct smscore_buffer_t *cb =
		kmalloc(sizeof(struct smscore_buffer_t), GFP_KERNEL);
	if (!cb) {
		sms_info("kmalloc(...) failed");
		return NULL;
	}

	cb->p = buffer;
	cb->offset_in_common = buffer - (u8 *) common_buffer;
	cb->phys = common_buffer_phys + cb->offset_in_common;

	return cb;
}
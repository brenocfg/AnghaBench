#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct isp1760_hcd {TYPE_1__* memory_pool; } ;
struct TYPE_2__ {scalar_t__ size; int free; scalar_t__ start; } ;

/* Variables and functions */
 int BLOCKS ; 
 int BLOCK_1_NUM ; 
 scalar_t__ BLOCK_1_SIZE ; 
 int BLOCK_2_NUM ; 
 scalar_t__ BLOCK_2_SIZE ; 
 scalar_t__ BLOCK_3_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PAYLOAD_SIZE ; 

__attribute__((used)) static void init_memory(struct isp1760_hcd *priv)
{
	int i;
	u32 payload;

	payload = 0x1000;
	for (i = 0; i < BLOCK_1_NUM; i++) {
		priv->memory_pool[i].start = payload;
		priv->memory_pool[i].size = BLOCK_1_SIZE;
		priv->memory_pool[i].free = 1;
		payload += priv->memory_pool[i].size;
	}


	for (i = BLOCK_1_NUM; i < BLOCK_1_NUM + BLOCK_2_NUM; i++) {
		priv->memory_pool[i].start = payload;
		priv->memory_pool[i].size = BLOCK_2_SIZE;
		priv->memory_pool[i].free = 1;
		payload += priv->memory_pool[i].size;
	}


	for (i = BLOCK_1_NUM + BLOCK_2_NUM; i < BLOCKS; i++) {
		priv->memory_pool[i].start = payload;
		priv->memory_pool[i].size = BLOCK_3_SIZE;
		priv->memory_pool[i].free = 1;
		payload += priv->memory_pool[i].size;
	}

	BUG_ON(payload - priv->memory_pool[i - 1].size > PAYLOAD_SIZE);
}
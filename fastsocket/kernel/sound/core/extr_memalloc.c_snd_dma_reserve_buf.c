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
struct snd_dma_buffer {int dummy; } ;
struct snd_mem_list {unsigned int id; int /*<<< orphan*/  list; struct snd_dma_buffer buffer; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 struct snd_mem_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_mutex ; 
 int /*<<< orphan*/  mem_list_head ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int snd_dma_reserve_buf(struct snd_dma_buffer *dmab, unsigned int id)
{
	struct snd_mem_list *mem;

	if (WARN_ON(!dmab))
		return -EINVAL;
	mem = kmalloc(sizeof(*mem), GFP_KERNEL);
	if (! mem)
		return -ENOMEM;
	mutex_lock(&list_mutex);
	mem->buffer = *dmab;
	mem->id = id;
	list_add_tail(&mem->list, &mem_list_head);
	mutex_unlock(&list_mutex);
	return 0;
}
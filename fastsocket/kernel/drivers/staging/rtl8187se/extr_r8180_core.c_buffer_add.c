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
typedef  int /*<<< orphan*/  u32 ;
struct buffer {struct buffer* next; void* dma; int /*<<< orphan*/ * buf; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMESGE (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

short buffer_add(struct buffer **buffer, u32 *buf, dma_addr_t dma,
		struct buffer **bufferhead)
{
        struct buffer *tmp;

	if(! *buffer){

		*buffer = kmalloc(sizeof(struct buffer),GFP_KERNEL);

		if (*buffer == NULL) {
			DMESGE("Failed to kmalloc head of TX/RX struct");
			return -1;
		}
		(*buffer)->next=*buffer;
		(*buffer)->buf=buf;
		(*buffer)->dma=dma;
		if(bufferhead !=NULL)
			(*bufferhead) = (*buffer);
		return 0;
	}
	tmp=*buffer;

	while(tmp->next!=(*buffer)) tmp=tmp->next;
	if ((tmp->next= kmalloc(sizeof(struct buffer),GFP_KERNEL)) == NULL){
		DMESGE("Failed to kmalloc TX/RX struct");
		return -1;
	}
	tmp->next->buf=buf;
	tmp->next->dma=dma;
	tmp->next->next=*buffer;

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i2o_device {scalar_t__ base_addr_virt; scalar_t__ msg_addr_virt; scalar_t__ FwDebugBuffer_P; int lct_size; int reply_fifo_size; int top_scsi_channel; int /*<<< orphan*/  unit; TYPE_3__* pDev; struct i2o_device* next_lun; TYPE_2__* channel; struct i2o_device* next; struct i2o_device* devices; int /*<<< orphan*/  reply_pool_pa; TYPE_5__* reply_pool; int /*<<< orphan*/  status_block_pa; TYPE_5__* status_block; int /*<<< orphan*/  lct_pa; TYPE_5__* lct; int /*<<< orphan*/  hrt_pa; TYPE_5__* hrt; TYPE_1__* host; } ;
struct adpt_device {scalar_t__ base_addr_virt; scalar_t__ msg_addr_virt; scalar_t__ FwDebugBuffer_P; int lct_size; int reply_fifo_size; int top_scsi_channel; int /*<<< orphan*/  unit; TYPE_3__* pDev; struct adpt_device* next_lun; TYPE_2__* channel; struct adpt_device* next; struct adpt_device* devices; int /*<<< orphan*/  reply_pool_pa; TYPE_5__* reply_pool; int /*<<< orphan*/  status_block_pa; TYPE_5__* status_block; int /*<<< orphan*/  lct_pa; TYPE_5__* lct; int /*<<< orphan*/  hrt_pa; TYPE_5__* hrt; TYPE_1__* host; } ;
typedef  int /*<<< orphan*/  i2o_status_block ;
typedef  struct i2o_device adpt_hba ;
struct TYPE_9__ {int num_entries; int entry_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {struct i2o_device** device; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPTI_I2O_MAJOR ; 
 int /*<<< orphan*/  DPT_DRIVER ; 
 int MAX_ID ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REPLY_FRAME_SIZE ; 
 int /*<<< orphan*/  adpt_configuration_lock ; 
 int /*<<< orphan*/ * adpt_sysfs_class ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct i2o_device*) ; 
 struct i2o_device* hba_chain ; 
 scalar_t__ hba_count ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct i2o_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_3__*) ; 
 int /*<<< orphan*/  unregister_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adpt_i2o_delete_hba(adpt_hba* pHba)
{
	adpt_hba* p1;
	adpt_hba* p2;
	struct i2o_device* d;
	struct i2o_device* next;
	int i;
	int j;
	struct adpt_device* pDev;
	struct adpt_device* pNext;


	mutex_lock(&adpt_configuration_lock);
	// scsi_unregister calls our adpt_release which
	// does a quiese
	if(pHba->host){
		free_irq(pHba->host->irq, pHba);
	}
	p2 = NULL;
	for( p1 = hba_chain; p1; p2 = p1,p1=p1->next){
		if(p1 == pHba) {
			if(p2) {
				p2->next = p1->next;
			} else {
				hba_chain = p1->next;
			}
			break;
		}
	}

	hba_count--;
	mutex_unlock(&adpt_configuration_lock);

	iounmap(pHba->base_addr_virt);
	pci_release_regions(pHba->pDev);
	if(pHba->msg_addr_virt != pHba->base_addr_virt){
		iounmap(pHba->msg_addr_virt);
	}
	if(pHba->FwDebugBuffer_P)
	   	iounmap(pHba->FwDebugBuffer_P);
	if(pHba->hrt) {
		dma_free_coherent(&pHba->pDev->dev,
			pHba->hrt->num_entries * pHba->hrt->entry_len << 2,
			pHba->hrt, pHba->hrt_pa);
	}
	if(pHba->lct) {
		dma_free_coherent(&pHba->pDev->dev, pHba->lct_size,
			pHba->lct, pHba->lct_pa);
	}
	if(pHba->status_block) {
		dma_free_coherent(&pHba->pDev->dev, sizeof(i2o_status_block),
			pHba->status_block, pHba->status_block_pa);
	}
	if(pHba->reply_pool) {
		dma_free_coherent(&pHba->pDev->dev,
			pHba->reply_fifo_size * REPLY_FRAME_SIZE * 4,
			pHba->reply_pool, pHba->reply_pool_pa);
	}

	for(d = pHba->devices; d ; d = next){
		next = d->next;
		kfree(d);
	}
	for(i = 0 ; i < pHba->top_scsi_channel ; i++){
		for(j = 0; j < MAX_ID; j++){
			if(pHba->channel[i].device[j] != NULL){
				for(pDev = pHba->channel[i].device[j]; pDev; pDev = pNext){
					pNext = pDev->next_lun;
					kfree(pDev);
				}
			}
		}
	}
	pci_dev_put(pHba->pDev);
	kfree(pHba);

	if (adpt_sysfs_class)
		device_destroy(adpt_sysfs_class,
				MKDEV(DPTI_I2O_MAJOR, pHba->unit));

	if(hba_count <= 0){
		unregister_chrdev(DPTI_I2O_MAJOR, DPT_DRIVER);   
		if (adpt_sysfs_class) {
			class_destroy(adpt_sysfs_class);
			adpt_sysfs_class = NULL;
		}
	}
}
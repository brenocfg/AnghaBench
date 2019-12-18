#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct sequencer_file_header {size_t csum; size_t major; size_t minor; size_t cseq_table_offset; size_t cseq_table_size; size_t lseq_table_offset; size_t lseq_table_size; size_t cseq_code_offset; size_t cseq_code_size; size_t lseq_code_offset; size_t lseq_code_size; void* lseq_idle_loop; void* cseq_idle_loop; void* mode2_task; int /*<<< orphan*/  version; } ;
struct asd_ha_struct {TYPE_1__* pcidev; } ;
struct TYPE_5__ {scalar_t__* data; int size; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CSEQ_NUM_VECS ; 
 int EINVAL ; 
 int LSEQ_NUM_VECS ; 
 int /*<<< orphan*/  SAS_RAZOR_SEQUENCER_FW_FILE ; 
 scalar_t__ SAS_RAZOR_SEQUENCER_FW_MAJOR ; 
 int /*<<< orphan*/  asd_printk (char*,...) ; 
 scalar_t__* cseq_code ; 
 size_t cseq_code_size ; 
 void* cseq_idle_loop ; 
 void** cseq_vecs ; 
 void* le16_to_cpu (void*) ; 
 void* le32_to_cpu (size_t) ; 
 scalar_t__* lseq_code ; 
 size_t lseq_code_size ; 
 void* lseq_idle_loop ; 
 void** lseq_vecs ; 
 void* mode2_task ; 
 int request_firmware (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* sequencer_fw ; 

__attribute__((used)) static int asd_request_firmware(struct asd_ha_struct *asd_ha)
{
	int err, i;
	struct sequencer_file_header header;
	const struct sequencer_file_header *hdr_ptr;
	u32 csum = 0;
	u16 *ptr_cseq_vecs, *ptr_lseq_vecs;

	if (sequencer_fw)
		/* already loaded */
		return 0;

	err = request_firmware(&sequencer_fw,
			       SAS_RAZOR_SEQUENCER_FW_FILE,
			       &asd_ha->pcidev->dev);
	if (err)
		return err;

	hdr_ptr = (const struct sequencer_file_header *)sequencer_fw->data;

	header.csum = le32_to_cpu(hdr_ptr->csum);
	header.major = le32_to_cpu(hdr_ptr->major);
	header.minor = le32_to_cpu(hdr_ptr->minor);
	header.cseq_table_offset = le32_to_cpu(hdr_ptr->cseq_table_offset);
	header.cseq_table_size = le32_to_cpu(hdr_ptr->cseq_table_size);
	header.lseq_table_offset = le32_to_cpu(hdr_ptr->lseq_table_offset);
	header.lseq_table_size = le32_to_cpu(hdr_ptr->lseq_table_size);
	header.cseq_code_offset = le32_to_cpu(hdr_ptr->cseq_code_offset);
	header.cseq_code_size = le32_to_cpu(hdr_ptr->cseq_code_size);
	header.lseq_code_offset = le32_to_cpu(hdr_ptr->lseq_code_offset);
	header.lseq_code_size = le32_to_cpu(hdr_ptr->lseq_code_size);
	header.mode2_task = le16_to_cpu(hdr_ptr->mode2_task);
	header.cseq_idle_loop = le16_to_cpu(hdr_ptr->cseq_idle_loop);
	header.lseq_idle_loop = le16_to_cpu(hdr_ptr->lseq_idle_loop);

	for (i = sizeof(header.csum); i < sequencer_fw->size; i++)
		csum += sequencer_fw->data[i];

	if (csum != header.csum) {
		asd_printk("Firmware file checksum mismatch\n");
		return -EINVAL;
	}

	if (header.cseq_table_size != CSEQ_NUM_VECS ||
	    header.lseq_table_size != LSEQ_NUM_VECS) {
		asd_printk("Firmware file table size mismatch\n");
		return -EINVAL;
	}

	asd_printk("Found sequencer Firmware version %d.%d (%s)\n",
		   header.major, header.minor, hdr_ptr->version);

	if (header.major != SAS_RAZOR_SEQUENCER_FW_MAJOR) {
		asd_printk("Firmware Major Version Mismatch;"
			   "driver requires version %d.X",
			   SAS_RAZOR_SEQUENCER_FW_MAJOR);
		return -EINVAL;
	}

	ptr_cseq_vecs = (u16 *)&sequencer_fw->data[header.cseq_table_offset];
	ptr_lseq_vecs = (u16 *)&sequencer_fw->data[header.lseq_table_offset];
	mode2_task = header.mode2_task;
	cseq_idle_loop = header.cseq_idle_loop;
	lseq_idle_loop = header.lseq_idle_loop;

	for (i = 0; i < CSEQ_NUM_VECS; i++)
		cseq_vecs[i] = le16_to_cpu(ptr_cseq_vecs[i]);

	for (i = 0; i < LSEQ_NUM_VECS; i++)
		lseq_vecs[i] = le16_to_cpu(ptr_lseq_vecs[i]);

	cseq_code = &sequencer_fw->data[header.cseq_code_offset];
	cseq_code_size = header.cseq_code_size;
	lseq_code = &sequencer_fw->data[header.lseq_code_offset];
	lseq_code_size = header.lseq_code_size;

	return 0;
}
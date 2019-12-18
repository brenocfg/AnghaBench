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
typedef  scalar_t__ u32 ;
struct ses_device {int* page1; unsigned char* page10; int page10_len; } ;
struct scsi_device {int dummy; } ;
struct enclosure_device {struct enclosure_component* component; struct ses_device* scratch; } ;
struct enclosure_component {int dummy; } ;

/* Variables and functions */
 unsigned char ENCLOSURE_COMPONENT_ARRAY_DEVICE ; 
 unsigned char ENCLOSURE_COMPONENT_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INIT_ALLOC_SIZE ; 
 int /*<<< orphan*/  IS_ERR (struct enclosure_component*) ; 
 struct enclosure_component* enclosure_component_register (struct enclosure_device*,int /*<<< orphan*/ ,unsigned char,char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ses_process_descriptor (struct enclosure_component*,unsigned char*) ; 
 scalar_t__ ses_recv_diag (struct scsi_device*,int,unsigned char*,int) ; 

__attribute__((used)) static void ses_enclosure_data_process(struct enclosure_device *edev,
				       struct scsi_device *sdev,
				       int create)
{
	u32 result;
	unsigned char *buf = NULL, *type_ptr, *desc_ptr, *addl_desc_ptr = NULL;
	int i, j, page7_len, len, components;
	struct ses_device *ses_dev = edev->scratch;
	int types = ses_dev->page1[10];
	unsigned char *hdr_buf = kzalloc(INIT_ALLOC_SIZE, GFP_KERNEL);

	if (!hdr_buf)
		goto simple_populate;

	/* re-read page 10 */
	if (ses_dev->page10)
		ses_recv_diag(sdev, 10, ses_dev->page10, ses_dev->page10_len);
	/* Page 7 for the descriptors is optional */
	result = ses_recv_diag(sdev, 7, hdr_buf, INIT_ALLOC_SIZE);
	if (result)
		goto simple_populate;

	page7_len = len = (hdr_buf[2] << 8) + hdr_buf[3] + 4;
	/* add 1 for trailing '\0' we'll use */
	buf = kzalloc(len + 1, GFP_KERNEL);
	if (!buf)
		goto simple_populate;
	result = ses_recv_diag(sdev, 7, buf, len);
	if (result) {
 simple_populate:
		kfree(buf);
		buf = NULL;
		desc_ptr = NULL;
		len = 0;
		page7_len = 0;
	} else {
		desc_ptr = buf + 8;
		len = (desc_ptr[2] << 8) + desc_ptr[3];
		/* skip past overall descriptor */
		desc_ptr += len + 4;
		if (ses_dev->page10)
			addl_desc_ptr = ses_dev->page10 + 8;
	}
	type_ptr = ses_dev->page1 + 12 + ses_dev->page1[11];
	components = 0;
	for (i = 0; i < types; i++, type_ptr += 4) {
		for (j = 0; j < type_ptr[1]; j++) {
			char *name = NULL;
			struct enclosure_component *ecomp;

			if (desc_ptr) {
				if (desc_ptr >= buf + page7_len) {
					desc_ptr = NULL;
				} else {
					len = (desc_ptr[2] << 8) + desc_ptr[3];
					desc_ptr += 4;
					/* Add trailing zero - pushes into
					 * reserved space */
					desc_ptr[len] = '\0';
					name = desc_ptr;
				}
			}
			if (type_ptr[0] == ENCLOSURE_COMPONENT_DEVICE ||
			    type_ptr[0] == ENCLOSURE_COMPONENT_ARRAY_DEVICE) {

				if (create)
					ecomp =	enclosure_component_register(edev,
									     components++,
									     type_ptr[0],
									     name);
				else
					ecomp = &edev->component[components++];

				if (!IS_ERR(ecomp) && addl_desc_ptr)
					ses_process_descriptor(ecomp,
							       addl_desc_ptr);
			}
			if (desc_ptr)
				desc_ptr += len;

			if (addl_desc_ptr)
				addl_desc_ptr += addl_desc_ptr[1] + 2;

		}
	}
	kfree(buf);
	kfree(hdr_buf);
}
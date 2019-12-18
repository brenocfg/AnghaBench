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
struct iser_page_vec {int length; int data_size; scalar_t__ offset; } ;
struct iser_data_buf {int /*<<< orphan*/  dma_nents; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int SIZE_4K ; 
 int /*<<< orphan*/  iser_data_buf_dump (struct iser_data_buf*,struct ib_device*) ; 
 int /*<<< orphan*/  iser_dbg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  iser_dump_page_vec (struct iser_page_vec*) ; 
 int /*<<< orphan*/  iser_err (char*) ; 
 int iser_sg_to_page_vec (struct iser_data_buf*,struct iser_page_vec*,struct ib_device*) ; 

__attribute__((used)) static void iser_page_vec_build(struct iser_data_buf *data,
				struct iser_page_vec *page_vec,
				struct ib_device *ibdev)
{
	int page_vec_len = 0;

	page_vec->length = 0;
	page_vec->offset = 0;

	iser_dbg("Translating sg sz: %d\n", data->dma_nents);
	page_vec_len = iser_sg_to_page_vec(data, page_vec, ibdev);
	iser_dbg("sg len %d page_vec_len %d\n", data->dma_nents,page_vec_len);

	page_vec->length = page_vec_len;

	if (page_vec_len * SIZE_4K < page_vec->data_size) {
		iser_err("page_vec too short to hold this SG\n");
		iser_data_buf_dump(data, ibdev);
		iser_dump_page_vec(page_vec);
		BUG();
	}
}
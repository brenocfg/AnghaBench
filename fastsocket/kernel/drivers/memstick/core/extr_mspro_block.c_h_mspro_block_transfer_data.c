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
struct scatterlist {int /*<<< orphan*/  member_0; } ;
struct mspro_block_data {unsigned char transfer_cmd; int caps; int current_page; size_t current_seg; int page_size; size_t seg_count; int /*<<< orphan*/  data_dir; TYPE_1__* req_sg; } ;
struct memstick_request {int tpc; int need_card_int; unsigned char int_reg; unsigned char* data; scalar_t__ error; } ;
struct memstick_dev {int /*<<< orphan*/  next_request; } ;
struct TYPE_2__ {int length; size_t offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int MEMSTICK_CAP_AUTO_GET_INT ; 
 unsigned char MEMSTICK_INT_BREQ ; 
 unsigned char MEMSTICK_INT_CED ; 
 unsigned char MEMSTICK_INT_CMDNAK ; 
 unsigned char MEMSTICK_INT_ERR ; 
 unsigned char MSPRO_CMD_STOP ; 
#define  MS_TPC_GET_INT 132 
#define  MS_TPC_READ_LONG_DATA 131 
#define  MS_TPC_SET_CMD 130 
#define  MS_TPC_WRITE_LONG_DATA 129 
#define  MS_TPC_WRITE_REG 128 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  h_mspro_block_default ; 
 int /*<<< orphan*/  h_mspro_block_wait_for_ced ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  memstick_init_req (struct memstick_request*,int const,unsigned char*,int) ; 
 int /*<<< orphan*/  memstick_init_req_sg (struct memstick_request*,int,struct scatterlist*) ; 
 int mspro_block_complete_req (struct memstick_dev*,scalar_t__) ; 
 int /*<<< orphan*/  nth_page (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  offset_in_page (size_t) ; 
 int /*<<< orphan*/  sg_page (TYPE_1__*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int h_mspro_block_transfer_data(struct memstick_dev *card,
				       struct memstick_request **mrq)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);
	unsigned char t_val = 0;
	struct scatterlist t_sg = { 0 };
	size_t t_offset;

	if ((*mrq)->error)
		return mspro_block_complete_req(card, (*mrq)->error);

	switch ((*mrq)->tpc) {
	case MS_TPC_WRITE_REG:
		memstick_init_req(*mrq, MS_TPC_SET_CMD, &msb->transfer_cmd, 1);
		(*mrq)->need_card_int = 1;
		return 0;
	case MS_TPC_SET_CMD:
		t_val = (*mrq)->int_reg;
		memstick_init_req(*mrq, MS_TPC_GET_INT, NULL, 1);
		if (msb->caps & MEMSTICK_CAP_AUTO_GET_INT)
			goto has_int_reg;
		return 0;
	case MS_TPC_GET_INT:
		t_val = (*mrq)->data[0];
has_int_reg:
		if (t_val & (MEMSTICK_INT_CMDNAK | MEMSTICK_INT_ERR)) {
			t_val = MSPRO_CMD_STOP;
			memstick_init_req(*mrq, MS_TPC_SET_CMD, &t_val, 1);
			card->next_request = h_mspro_block_default;
			return 0;
		}

		if (msb->current_page
		    == (msb->req_sg[msb->current_seg].length
			/ msb->page_size)) {
			msb->current_page = 0;
			msb->current_seg++;

			if (msb->current_seg == msb->seg_count) {
				if (t_val & MEMSTICK_INT_CED) {
					return mspro_block_complete_req(card,
									0);
				} else {
					card->next_request
						= h_mspro_block_wait_for_ced;
					memstick_init_req(*mrq, MS_TPC_GET_INT,
							  NULL, 1);
					return 0;
				}
			}
		}

		if (!(t_val & MEMSTICK_INT_BREQ)) {
			memstick_init_req(*mrq, MS_TPC_GET_INT, NULL, 1);
			return 0;
		}

		t_offset = msb->req_sg[msb->current_seg].offset;
		t_offset += msb->current_page * msb->page_size;

		sg_set_page(&t_sg,
			    nth_page(sg_page(&(msb->req_sg[msb->current_seg])),
				     t_offset >> PAGE_SHIFT),
			    msb->page_size, offset_in_page(t_offset));

		memstick_init_req_sg(*mrq, msb->data_dir == READ
					   ? MS_TPC_READ_LONG_DATA
					   : MS_TPC_WRITE_LONG_DATA,
				     &t_sg);
		(*mrq)->need_card_int = 1;
		return 0;
	case MS_TPC_READ_LONG_DATA:
	case MS_TPC_WRITE_LONG_DATA:
		msb->current_page++;
		if (msb->caps & MEMSTICK_CAP_AUTO_GET_INT) {
			t_val = (*mrq)->int_reg;
			goto has_int_reg;
		} else {
			memstick_init_req(*mrq, MS_TPC_GET_INT, NULL, 1);
			return 0;
		}

	default:
		BUG();
	}
}
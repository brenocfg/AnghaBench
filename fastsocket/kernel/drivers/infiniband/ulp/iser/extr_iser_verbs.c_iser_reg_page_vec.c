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
typedef  scalar_t__ u64 ;
struct iser_page_vec {int length; int data_size; scalar_t__* pages; scalar_t__ offset; } ;
struct iser_mem_reg {int len; int is_fmr; scalar_t__ va; void* mem_h; scalar_t__ lkey; int /*<<< orphan*/  rkey; } ;
struct iser_conn {int /*<<< orphan*/  fmr_pool; } ;
struct ib_pool_fmr {TYPE_1__* fmr; } ;
struct TYPE_2__ {int /*<<< orphan*/  rkey; scalar_t__ lkey; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ib_pool_fmr*) ; 
 scalar_t__ PTR_ERR (struct ib_pool_fmr*) ; 
 int SIZE_4K ; 
 struct ib_pool_fmr* ib_fmr_pool_map_phys (int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  iser_dbg (char*,struct iser_page_vec*,int,unsigned long,unsigned long,unsigned int,void*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 

int iser_reg_page_vec(struct iser_conn     *ib_conn,
		      struct iser_page_vec *page_vec,
		      struct iser_mem_reg  *mem_reg)
{
	struct ib_pool_fmr *mem;
	u64		   io_addr;
	u64		   *page_list;
	int		   status;

	page_list = page_vec->pages;
	io_addr	  = page_list[0];

	mem  = ib_fmr_pool_map_phys(ib_conn->fmr_pool,
				    page_list,
				    page_vec->length,
				    io_addr);

	if (IS_ERR(mem)) {
		status = (int)PTR_ERR(mem);
		iser_err("ib_fmr_pool_map_phys failed: %d\n", status);
		return status;
	}

	mem_reg->lkey  = mem->fmr->lkey;
	mem_reg->rkey  = mem->fmr->rkey;
	mem_reg->len   = page_vec->length * SIZE_4K;
	mem_reg->va    = io_addr;
	mem_reg->is_fmr = 1;
	mem_reg->mem_h = (void *)mem;

	mem_reg->va   += page_vec->offset;
	mem_reg->len   = page_vec->data_size;

	iser_dbg("PHYSICAL Mem.register, [PHYS p_array: 0x%p, sz: %d, "
		 "entry[0]: (0x%08lx,%ld)] -> "
		 "[lkey: 0x%08X mem_h: 0x%p va: 0x%08lX sz: %ld]\n",
		 page_vec, page_vec->length,
		 (unsigned long)page_vec->pages[0],
		 (unsigned long)page_vec->data_size,
		 (unsigned int)mem_reg->lkey, mem_reg->mem_h,
		 (unsigned long)mem_reg->va, (unsigned long)mem_reg->len);
	return 0;
}
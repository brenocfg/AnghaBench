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
typedef  unsigned int u32 ;
struct efx_nic {int dummy; } ;
struct efx_memcpy_req {unsigned int to_rid; int to_addr; unsigned int from_rid; int from_addr; unsigned int length; int /*<<< orphan*/ * from_buf; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MCDI_CTL_SDU_LEN_MAX ; 
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  MC_CMD_MEMCPY ; 
 unsigned int MC_CMD_MEMCPY_IN_LEN (unsigned int) ; 
 int /*<<< orphan*/  MC_CMD_MEMCPY_IN_RECORD_LEN ; 
 unsigned int MC_CMD_MEMCPY_RECORD_TYPEDEF_RID_INLINE ; 
 int /*<<< orphan*/  MEMCPY_IN_RECORD ; 
 int /*<<< orphan*/  MEMCPY_RECORD_TYPEDEF_FROM_ADDR_HI ; 
 int /*<<< orphan*/  MEMCPY_RECORD_TYPEDEF_FROM_ADDR_LO ; 
 int /*<<< orphan*/  MEMCPY_RECORD_TYPEDEF_FROM_RID ; 
 int /*<<< orphan*/  MEMCPY_RECORD_TYPEDEF_LENGTH ; 
 int /*<<< orphan*/  MEMCPY_RECORD_TYPEDEF_TO_ADDR_HI ; 
 int /*<<< orphan*/  MEMCPY_RECORD_TYPEDEF_TO_ADDR_LO ; 
 int /*<<< orphan*/  MEMCPY_RECORD_TYPEDEF_TO_RID ; 
 scalar_t__ WARN_ON (int) ; 
 int efx_mcdi_rpc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int efx_sriov_memcpy(struct efx_nic *efx, struct efx_memcpy_req *req,
			    unsigned int count)
{
	u8 *inbuf, *record;
	unsigned int used;
	u32 from_rid, from_hi, from_lo;
	int rc;

	mb();	/* Finish writing source/reading dest before DMA starts */

	used = MC_CMD_MEMCPY_IN_LEN(count);
	if (WARN_ON(used > MCDI_CTL_SDU_LEN_MAX))
		return -ENOBUFS;

	/* Allocate room for the largest request */
	inbuf = kzalloc(MCDI_CTL_SDU_LEN_MAX, GFP_KERNEL);
	if (inbuf == NULL)
		return -ENOMEM;

	record = inbuf;
	MCDI_SET_DWORD(record, MEMCPY_IN_RECORD, count);
	while (count-- > 0) {
		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_TO_RID,
			       req->to_rid);
		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_TO_ADDR_LO,
			       (u32)req->to_addr);
		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_TO_ADDR_HI,
			       (u32)(req->to_addr >> 32));
		if (req->from_buf == NULL) {
			from_rid = req->from_rid;
			from_lo = (u32)req->from_addr;
			from_hi = (u32)(req->from_addr >> 32);
		} else {
			if (WARN_ON(used + req->length > MCDI_CTL_SDU_LEN_MAX)) {
				rc = -ENOBUFS;
				goto out;
			}

			from_rid = MC_CMD_MEMCPY_RECORD_TYPEDEF_RID_INLINE;
			from_lo = used;
			from_hi = 0;
			memcpy(inbuf + used, req->from_buf, req->length);
			used += req->length;
		}

		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_FROM_RID, from_rid);
		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_FROM_ADDR_LO,
			       from_lo);
		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_FROM_ADDR_HI,
			       from_hi);
		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_LENGTH,
			       req->length);

		++req;
		record += MC_CMD_MEMCPY_IN_RECORD_LEN;
	}

	rc = efx_mcdi_rpc(efx, MC_CMD_MEMCPY, inbuf, used, NULL, 0, NULL);
out:
	kfree(inbuf);

	mb();	/* Don't write source/read dest before DMA is complete */

	return rc;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {unsigned int qdio_error; int sbal_index; int sbal_count; int scount; int /*<<< orphan*/  fsf_reqid; } ;
struct TYPE_4__ {TYPE_1__ qdio; } ;
struct zfcp_dbf_hba_record {int total_size; int offset; int size; int /*<<< orphan*/  tag; scalar_t__ data; TYPE_2__ u; } ;
struct zfcp_dbf_dump {int total_size; int offset; int size; int /*<<< orphan*/  tag; scalar_t__ data; TYPE_2__ u; } ;
struct zfcp_dbf {int /*<<< orphan*/  hba_lock; int /*<<< orphan*/  hba; struct zfcp_dbf_hba_record hba_buf; } ;
struct qdio_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_DBF_TAG_SIZE ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int,struct zfcp_dbf_hba_record*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_hba_record*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void zfcp_dbf_hba_qdio(struct zfcp_dbf *dbf, unsigned int qdio_error,
		       int sbal_index, int sbal_count,
		       u32 req_id, u8 scount, void *pl[])
{
	struct zfcp_dbf_hba_record *r = &dbf->hba_buf;
	unsigned long flags;
	int level = 0;

	spin_lock_irqsave(&dbf->hba_lock, flags);
	memset(r, 0, sizeof(*r));
	strncpy(r->tag, "qdio", ZFCP_DBF_TAG_SIZE);
	r->u.qdio.qdio_error = qdio_error;
	r->u.qdio.sbal_index = sbal_index;
	r->u.qdio.sbal_count = sbal_count;
	if (pl) {
		r->u.qdio.fsf_reqid = req_id;
		r->u.qdio.scount = scount;
	}
	debug_event(dbf->hba, level, r, sizeof(*r));
	if (pl) {
		struct zfcp_dbf_dump *dump = (struct zfcp_dbf_dump *)r;
		int pl_idx, sbal_off, dbf_off, sbal_tail, dbf_tail, chunk,
			dump_off, dump_chunk;
		/* The dump consists of one or more dbf records which
		   are filled densely and copied chunk-wise from one
		   or more sbals pointed to by pl vector. sbals have a
		   different size than dbf records. */
		pl_idx = 0;
		sbal_off = 0;
		sbal_tail = sizeof(struct qdio_buffer);
		dbf_off = 0;
		dbf_tail = sizeof(*r) - sizeof(*dump)/*headroom*/;
		dump_off = 0;
		dump_chunk = 0;
		memset(r, 0, sizeof(*r));
		strncpy(dump->tag, "dump", ZFCP_DBF_TAG_SIZE);
		dump->total_size = scount * sizeof(struct qdio_buffer);
		dump->offset = dump_off;
		for (;;) {
			chunk = min(sbal_tail, dbf_tail);
			if (pl_idx >= scount || !pl[pl_idx]) {
				if (dbf_off) { /* last (partial) dbf record */
					dump->size = dump_chunk;
					debug_event(dbf->hba, level, dump,
						    dump->size + sizeof(*dump));
				}
				break;
			}
			memcpy(dump->data + dbf_off,
			       pl[pl_idx] + sbal_off, chunk);
			sbal_off  += chunk;
			sbal_tail -= chunk;
			dbf_off   += chunk;
			dbf_tail  -= chunk;
			dump_chunk += chunk;
			if (!sbal_tail) { /* move to next sbal */
				pl_idx++;
				sbal_off = 0;
				sbal_tail = sizeof(struct qdio_buffer);
			}
			if (!dbf_tail) { /* move to next dbf record */
				dump->size = dump_chunk;
				debug_event(dbf->hba, level, dump,
					    dump->size + sizeof(*dump));
				dump_off += dump->size;
				dump_chunk = 0;
				dbf_off = 0;
				dbf_tail = sizeof(*r) - sizeof(*dump);
				memset(r, 0, sizeof(*r));
				strncpy(dump->tag, "dump", ZFCP_DBF_TAG_SIZE);
				dump->total_size =
					scount * sizeof(struct qdio_buffer);
				dump->offset = dump_off;
				/* continue; */
			}
		}
	} /* if (pl) */
	spin_unlock_irqrestore(&dbf->hba_lock, flags);
}
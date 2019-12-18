#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {int /*<<< orphan*/  val; int /*<<< orphan*/  low; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; int /*<<< orphan*/  low; } ;
struct TYPE_9__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  tag; int /*<<< orphan*/  host_no; TYPE_2__ timestamp; TYPE_1__ fnaddr; } ;
typedef  TYPE_3__ fnic_trace_data_t ;
struct TYPE_10__ {scalar_t__ buffer; } ;
typedef  TYPE_4__ fnic_dbgfs_t ;
struct TYPE_11__ {int rd_idx; int wr_idx; scalar_t__* page_offset; } ;

/* Variables and functions */
 int KSYM_SYMBOL_LEN ; 
 int PAGE_SIZE ; 
 int fnic_max_trace_entries ; 
 TYPE_5__ fnic_trace_entries ; 
 int /*<<< orphan*/  fnic_trace_lock ; 
 int /*<<< orphan*/  jiffies_to_timespec (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ snprintf (scalar_t__,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprint_symbol (char*,int /*<<< orphan*/ ) ; 
 int trace_max_pages ; 

int fnic_get_trace_data(fnic_dbgfs_t *fnic_dbgfs_prt)
{
	int rd_idx;
	int wr_idx;
	int len = 0;
	unsigned long flags;
	char str[KSYM_SYMBOL_LEN];
	struct timespec val;
	fnic_trace_data_t *tbp;

	spin_lock_irqsave(&fnic_trace_lock, flags);
	rd_idx = fnic_trace_entries.rd_idx;
	wr_idx = fnic_trace_entries.wr_idx;
	if (wr_idx < rd_idx) {
		while (1) {
			/* Start from read index @rd_idx */
			tbp = (fnic_trace_data_t *)
				  fnic_trace_entries.page_offset[rd_idx];
			if (!tbp) {
				spin_unlock_irqrestore(&fnic_trace_lock, flags);
				return 0;
			}
			/* Convert function pointer to function name */
			if (sizeof(unsigned long) < 8) {
				sprint_symbol(str, tbp->fnaddr.low);
				jiffies_to_timespec(tbp->timestamp.low, &val);
			} else {
				sprint_symbol(str, tbp->fnaddr.val);
				jiffies_to_timespec(tbp->timestamp.val, &val);
			}
			/*
			 * Dump trace buffer entry to memory file
			 * and increment read index @rd_idx
			 */
			len += snprintf(fnic_dbgfs_prt->buffer + len,
				  (trace_max_pages * PAGE_SIZE * 3) - len,
				  "%16lu.%16lu %-50s %8x %8x %16llx %16llx "
				  "%16llx %16llx %16llx\n", val.tv_sec,
				  val.tv_nsec, str, tbp->host_no, tbp->tag,
				  tbp->data[0], tbp->data[1], tbp->data[2],
				  tbp->data[3], tbp->data[4]);
			rd_idx++;
			/*
			 * If rd_idx is reached to maximum trace entries
			 * then move rd_idx to zero
			 */
			if (rd_idx > (fnic_max_trace_entries-1))
				rd_idx = 0;
			/*
			 * Continure dumpping trace buffer entries into
			 * memory file till rd_idx reaches write index
			 */
			if (rd_idx == wr_idx)
				break;
		}
	} else if (wr_idx > rd_idx) {
		while (1) {
			/* Start from read index @rd_idx */
			tbp = (fnic_trace_data_t *)
				  fnic_trace_entries.page_offset[rd_idx];
			if (!tbp) {
				spin_unlock_irqrestore(&fnic_trace_lock, flags);
				return 0;
			}
			/* Convert function pointer to function name */
			if (sizeof(unsigned long) < 8) {
				sprint_symbol(str, tbp->fnaddr.low);
				jiffies_to_timespec(tbp->timestamp.low, &val);
			} else {
				sprint_symbol(str, tbp->fnaddr.val);
				jiffies_to_timespec(tbp->timestamp.val, &val);
			}
			/*
			 * Dump trace buffer entry to memory file
			 * and increment read index @rd_idx
			 */
			len += snprintf(fnic_dbgfs_prt->buffer + len,
				  (trace_max_pages * PAGE_SIZE * 3) - len,
				  "%16lu.%16lu %-50s %8x %8x %16llx %16llx "
				  "%16llx %16llx %16llx\n", val.tv_sec,
				  val.tv_nsec, str, tbp->host_no, tbp->tag,
				  tbp->data[0], tbp->data[1], tbp->data[2],
				  tbp->data[3], tbp->data[4]);
			rd_idx++;
			/*
			 * Continue dumpping trace buffer entries into
			 * memory file till rd_idx reaches write index
			 */
			if (rd_idx == wr_idx)
				break;
		}
	}
	spin_unlock_irqrestore(&fnic_trace_lock, flags);
	return len;
}
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
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct qfq_class {int /*<<< orphan*/  cl_handle; int /*<<< orphan*/  cl_qif; } ;
typedef  scalar_t__ pktsched_bitmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  QFQIF_IFP (int /*<<< orphan*/ ) ; 
 int QFQ_MIN_SLOT_SHIFT ; 
 int QFQ_ONE_FP ; 
 int __fls (scalar_t__) ; 
 int /*<<< orphan*/  if_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 scalar_t__ pktsched_verbose ; 
 int /*<<< orphan*/  qfq_style (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qfq_calc_index(struct qfq_class *cl, u_int32_t inv_w, u_int32_t maxlen)
{
	u_int64_t slot_size = (u_int64_t)maxlen *inv_w;
	pktsched_bitmap_t size_map;
	int index = 0;

	size_map = (pktsched_bitmap_t)(slot_size >> QFQ_MIN_SLOT_SHIFT);
	if (!size_map)
		goto out;

	index = __fls(size_map) + 1;	/* basically a log_2() */
	index -= !(slot_size - (1ULL << (index + QFQ_MIN_SLOT_SHIFT - 1)));

	if (index < 0)
		index = 0;
out:
	if (pktsched_verbose) {
		log(LOG_DEBUG, "%s: %s qid=%d grp=%d W=%u, L=%u, I=%d\n",
		    if_name(QFQIF_IFP(cl->cl_qif)), qfq_style(cl->cl_qif),
		    cl->cl_handle, index, (u_int32_t)(QFQ_ONE_FP/inv_w),
		    maxlen, index);
	}
	return (index);
}
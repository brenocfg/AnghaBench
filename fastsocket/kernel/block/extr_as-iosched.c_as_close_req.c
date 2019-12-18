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
struct request {int dummy; } ;
struct as_io_context {scalar_t__ seek_samples; int seek_mean; } ;
struct as_data {int* last_sector; size_t batch_data_dir; scalar_t__ antic_status; unsigned long antic_start; unsigned long antic_expire; int new_seek_mean; int /*<<< orphan*/  ioc_finished; } ;
typedef  int sector_t ;

/* Variables and functions */
 scalar_t__ ANTIC_OFF ; 
 int HZ ; 
 int blk_rq_pos (struct request*) ; 
 unsigned long jiffies ; 

__attribute__((used)) static int as_close_req(struct as_data *ad, struct as_io_context *aic,
			struct request *rq)
{
	unsigned long delay;	/* jiffies */
	sector_t last = ad->last_sector[ad->batch_data_dir];
	sector_t next = blk_rq_pos(rq);
	sector_t delta; /* acceptable close offset (in sectors) */
	sector_t s;

	if (ad->antic_status == ANTIC_OFF || !ad->ioc_finished)
		delay = 0;
	else
		delay = jiffies - ad->antic_start;

	if (delay == 0)
		delta = 8192;
	else if (delay <= (20 * HZ / 1000) && delay <= ad->antic_expire)
		delta = 8192 << delay;
	else
		return 1;

	if ((last <= next + (delta>>1)) && (next <= last + delta))
		return 1;

	if (last < next)
		s = next - last;
	else
		s = last - next;

	if (aic->seek_samples == 0) {
		/*
		 * Process has just started IO. Use past statistics to
		 * gauge success possibility
		 */
		if (ad->new_seek_mean > s) {
			/* this request is better than what we're expecting */
			return 1;
		}

	} else {
		if (aic->seek_mean > s) {
			/* this request is better than what we're expecting */
			return 1;
		}
	}

	return 0;
}
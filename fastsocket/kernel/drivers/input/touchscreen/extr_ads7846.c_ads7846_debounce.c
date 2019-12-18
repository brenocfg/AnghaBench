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
struct ads7846 {scalar_t__ read_cnt; int last_read; scalar_t__ debounce_tol; scalar_t__ read_rep; scalar_t__ debounce_max; scalar_t__ debounce_rep; } ;

/* Variables and functions */
 int ADS7846_FILTER_IGNORE ; 
 int ADS7846_FILTER_OK ; 
 int ADS7846_FILTER_REPEAT ; 
 scalar_t__ abs (int) ; 

__attribute__((used)) static int ads7846_debounce(void *ads, int data_idx, int *val)
{
	struct ads7846		*ts = ads;

	if (!ts->read_cnt || (abs(ts->last_read - *val) > ts->debounce_tol)) {
		/* Start over collecting consistent readings. */
		ts->read_rep = 0;
		/* Repeat it, if this was the first read or the read
		 * wasn't consistent enough. */
		if (ts->read_cnt < ts->debounce_max) {
			ts->last_read = *val;
			ts->read_cnt++;
			return ADS7846_FILTER_REPEAT;
		} else {
			/* Maximum number of debouncing reached and still
			 * not enough number of consistent readings. Abort
			 * the whole sample, repeat it in the next sampling
			 * period.
			 */
			ts->read_cnt = 0;
			return ADS7846_FILTER_IGNORE;
		}
	} else {
		if (++ts->read_rep > ts->debounce_rep) {
			/* Got a good reading for this coordinate,
			 * go for the next one. */
			ts->read_cnt = 0;
			ts->read_rep = 0;
			return ADS7846_FILTER_OK;
		} else {
			/* Read more values that are consistent. */
			ts->read_cnt++;
			return ADS7846_FILTER_REPEAT;
		}
	}
}
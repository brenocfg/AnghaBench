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
typedef  size_t u8 ;
struct airq_t {int /*<<< orphan*/  drv_data; int /*<<< orphan*/  (* handler ) (scalar_t__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {unsigned long* word; scalar_t__* byte; } ;

/* Variables and functions */
 unsigned long INDICATOR_MASK ; 
 int NR_AIRQS_PER_WORD ; 
 int NR_AIRQ_WORDS ; 
 struct airq_t*** airqs ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_1__* indicators ; 
 scalar_t__ likely (struct airq_t*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,int /*<<< orphan*/ ) ; 

void do_adapter_IO(u8 isc)
{
	int w;
	int i;
	unsigned long word;
	struct airq_t *airq;

	/*
	 * Access indicator array in word-sized chunks to minimize storage
	 * fetch operations.
	 */
	for (w = 0; w < NR_AIRQ_WORDS; w++) {
		word = indicators[isc].word[w];
		i = w * NR_AIRQS_PER_WORD;
		/*
		 * Check bytes within word for active indicators.
		 */
		while (word) {
			if (word & INDICATOR_MASK) {
				airq = airqs[isc][i];
				/* Make sure gcc reads from airqs only once. */
				barrier();
				if (likely(airq))
					airq->handler(&indicators[isc].byte[i],
						      airq->drv_data);
				else
					/*
					 * Reset ill-behaved indicator.
					 */
					indicators[isc].byte[i] = 0;
			}
			word <<= 8;
			i++;
		}
	}
}
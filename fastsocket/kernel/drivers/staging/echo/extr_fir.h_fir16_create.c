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
struct fir16_state_t {int taps; int curr_pos; int /*<<< orphan*/  const* history; int /*<<< orphan*/  const* coeffs; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const int16_t *fir16_create(struct fir16_state_t *fir,
					      const int16_t *coeffs, int taps)
{
	fir->taps = taps;
	fir->curr_pos = taps - 1;
	fir->coeffs = coeffs;
#if defined(__bfin__)
	fir->history = kcalloc(2 * taps, sizeof(int16_t), GFP_KERNEL);
#else
	fir->history = kcalloc(taps, sizeof(int16_t), GFP_KERNEL);
#endif
	return fir->history;
}
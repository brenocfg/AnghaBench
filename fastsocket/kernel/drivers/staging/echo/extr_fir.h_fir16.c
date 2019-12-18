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
struct fir16_state_t {int* history; size_t curr_pos; size_t taps; int* coeffs; } ;
typedef  int int32_t ;
typedef  void* int16_t ;

/* Variables and functions */
 int dot_asm (void**,int*,size_t) ; 

__attribute__((used)) static inline int16_t fir16(struct fir16_state_t *fir, int16_t sample)
{
	int32_t y;
#if defined(__bfin__)
	fir->history[fir->curr_pos] = sample;
	fir->history[fir->curr_pos + fir->taps] = sample;
	y = dot_asm((int16_t *) fir->coeffs, &fir->history[fir->curr_pos],
		    fir->taps);
#else
	int i;
	int offset1;
	int offset2;

	fir->history[fir->curr_pos] = sample;

	offset2 = fir->curr_pos;
	offset1 = fir->taps - offset2;
	y = 0;
	for (i = fir->taps - 1; i >= offset1; i--)
		y += fir->coeffs[i] * fir->history[i - offset1];
	for (; i >= 0; i--)
		y += fir->coeffs[i] * fir->history[i + offset2];
#endif
	if (fir->curr_pos <= 0)
		fir->curr_pos = fir->taps;
	fir->curr_pos--;
	return (int16_t) (y >> 15);
}
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
typedef  size_t uint64_t ;
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t UINT64_MAX ; 
 scalar_t__ powf (float,int) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void
compute_stats(uint64_t *values, uint64_t count, float *averagep, uint64_t *maxp, uint64_t *minp, float *stddevp)
{
	uint32_t i;
	uint64_t _sum = 0;
	uint64_t _max = 0;
	uint64_t _min = UINT64_MAX;
	float	 _avg = 0;
	float 	 _dev = 0;

	for (i = 0; i < count; i++) {
		_sum += values[i];
		_max = values[i] > _max ? values[i] : _max;
		_min = values[i] < _min ? values[i] : _min;
	}

	_avg = ((float)_sum) / ((float)count);
	
	_dev = 0;
	for (i = 0; i < count; i++) {
		_dev += powf((((float)values[i]) - _avg), 2);
	}
	
	_dev /= count;
	_dev = sqrtf(_dev);

	*averagep = _avg;
	*maxp = _max;
	*minp = _min;
	*stddevp = _dev;
}
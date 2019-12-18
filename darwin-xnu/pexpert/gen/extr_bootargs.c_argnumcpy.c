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
struct i24 {long long i24; } ;
typedef  long long int8_t ;
typedef  long long int64_t ;
typedef  long long int32_t ;
typedef  long long int16_t ;

/* Variables and functions */

__attribute__((used)) static int argnumcpy(long long val, void *to, unsigned maxlen)
{
	switch (maxlen) {
		case 0:
			/* No write-back, caller just wants to know if arg was found */
			break;
		case 1:
			*(int8_t *)to = val;
			break;
		case 2:
			*(int16_t *)to = val;
			break;
		case 3:
			/* Unlikely in practice */
			((struct i24 *)to)->i24 = val;
			break;
		case 4:
			*(int32_t *)to = val;
			break;
		case 8:
			*(int64_t *)to = val;
			break;
		default:
			*(int32_t *)to = val;
			maxlen = 4;
			break;
	}

	return (int)maxlen;
}
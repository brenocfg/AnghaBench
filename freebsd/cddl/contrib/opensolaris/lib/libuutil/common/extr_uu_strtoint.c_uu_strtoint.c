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
typedef  scalar_t__ uint64_t ;
typedef  void* int8_t ;
typedef  void* int64_t ;
typedef  void* int32_t ;
typedef  void* int16_t ;

/* Variables and functions */
 void* INT16_MAX ; 
 void* INT16_MIN ; 
 void* INT32_MAX ; 
 void* INT32_MIN ; 
 void* INT64_MAX ; 
 void* INT64_MIN ; 
 void* INT8_MAX ; 
 void* INT8_MIN ; 
 int /*<<< orphan*/  UU_ERROR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  UU_ERROR_OVERFLOW ; 
 int /*<<< orphan*/  UU_ERROR_UNDERFLOW ; 
 int strtoint (char const*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  uu_set_error (int /*<<< orphan*/ ) ; 

int
uu_strtoint(const char *s, void *v, size_t sz, int base,
    int64_t min, int64_t max)
{
	uint64_t val_u;
	int64_t val;

	if (min > max)
		goto bad_argument;

	switch (sz) {
	case 1:
		if (max > INT8_MAX || min < INT8_MIN)
			goto bad_argument;
		break;
	case 2:
		if (max > INT16_MAX || min < INT16_MIN)
			goto bad_argument;
		break;
	case 4:
		if (max > INT32_MAX || min < INT32_MIN)
			goto bad_argument;
		break;
	case 8:
		if (max > INT64_MAX || min < INT64_MIN)
			goto bad_argument;
		break;
	default:
		goto bad_argument;
	}

	if (min == 0 && max == 0) {
		min = -(1ULL << (8 * sz - 1));
		max = (1ULL << (8 * sz - 1)) - 1;
	}

	if (strtoint(s, &val_u, base, 1) == -1)
		return (-1);

	val = (int64_t)val_u;

	if (val < min) {
		uu_set_error(UU_ERROR_UNDERFLOW);
		return (-1);
	} else if (val > max) {
		uu_set_error(UU_ERROR_OVERFLOW);
		return (-1);
	}

	switch (sz) {
	case 1:
		*(int8_t *)v = val;
		return (0);
	case 2:
		*(int16_t *)v = val;
		return (0);
	case 4:
		*(int32_t *)v = val;
		return (0);
	case 8:
		*(int64_t *)v = val;
		return (0);
	default:
		break;		/* fall through to bad_argument */
	}

bad_argument:
	uu_set_error(UU_ERROR_INVALID_ARGUMENT);
	return (-1);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pagemask; scalar_t__ page; scalar_t__ hour; scalar_t__ minute; int pgbuf; } ;
typedef  TYPE_1__ vtx_pagereq_t ;
struct saa5246a_device {int* is_searching; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_END ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ HOUR_MAX ; 
 int HR_TEN ; 
 int HR_UNIT ; 
 int HUNDREDS_OF_PAGE (scalar_t__) ; 
 scalar_t__ MINUTE_MAX ; 
 int MIN_TEN ; 
 int MIN_UNIT ; 
 int NUM_DAUS ; 
 scalar_t__ PAGE_MAX ; 
 int PGMASK_HOUR ; 
 int PGMASK_MAX ; 
 int PGMASK_MINUTE ; 
 int PGMASK_PAGE ; 
 int PG_HUND ; 
 int PG_TEN ; 
 int PG_UNIT ; 
 int R2_BANK_0 ; 
 int R2_HAMMING_CHECK_OFF ; 
 int R2_IN_R3_SELECT_PAGE_HUNDREDS ; 
 int R3_HOLD_PAGE ; 
 int R3_HOURS_TENS_DO_CARE ; 
 int R3_HOURS_TENS_DO_NOT_CARE ; 
 int R3_HOURS_UNITS_DO_CARE ; 
 int R3_HOURS_UNITS_DO_NOT_CARE ; 
 int R3_MINUTES_TENS_DO_CARE ; 
 int R3_MINUTES_TENS_DO_NOT_CARE ; 
 int R3_MINUTES_UNITS_DO_CARE ; 
 int R3_MINUTES_UNITS_DO_NOT_CARE ; 
 int R3_PAGE_HUNDREDS_DO_CARE ; 
 int R3_PAGE_HUNDREDS_DO_NOT_CARE ; 
 int R3_PAGE_TENS_DO_CARE ; 
 int R3_PAGE_TENS_DO_NOT_CARE ; 
 int R3_PAGE_UNITS_DO_CARE ; 
 int R3_PAGE_UNITS_DO_NOT_CARE ; 
 int R3_UPDATE_PAGE ; 
 int /*<<< orphan*/  SAA5246A_REGISTER_R2 ; 
 int TENS_OF_HOUR (scalar_t__) ; 
 int TENS_OF_MINUTE (scalar_t__) ; 
 int TENS_OF_PAGE (scalar_t__) ; 
 int UNITS_OF_HOUR (scalar_t__) ; 
 int UNITS_OF_MINUTE (scalar_t__) ; 
 int UNITS_OF_PAGE (scalar_t__) ; 
 scalar_t__ i2c_senddata (struct saa5246a_device*,int /*<<< orphan*/ ,int,int,int,...) ; 

__attribute__((used)) static int saa5246a_request_page(struct saa5246a_device *t,
    vtx_pagereq_t *req)
{
	if (req->pagemask < 0 || req->pagemask >= PGMASK_MAX)
		return -EINVAL;
	if (req->pagemask & PGMASK_PAGE)
		if (req->page < 0 || req->page > PAGE_MAX)
			return -EINVAL;
	if (req->pagemask & PGMASK_HOUR)
		if (req->hour < 0 || req->hour > HOUR_MAX)
			return -EINVAL;
	if (req->pagemask & PGMASK_MINUTE)
		if (req->minute < 0 || req->minute > MINUTE_MAX)
			return -EINVAL;
	if (req->pgbuf < 0 || req->pgbuf >= NUM_DAUS)
		return -EINVAL;

	if (i2c_senddata(t, SAA5246A_REGISTER_R2,

		R2_IN_R3_SELECT_PAGE_HUNDREDS |
		req->pgbuf << 4 |
		R2_BANK_0 |
		R2_HAMMING_CHECK_OFF,

		HUNDREDS_OF_PAGE(req->page) |
		R3_HOLD_PAGE |
		(req->pagemask & PG_HUND ?
			R3_PAGE_HUNDREDS_DO_CARE :
			R3_PAGE_HUNDREDS_DO_NOT_CARE),

		TENS_OF_PAGE(req->page) |
		(req->pagemask & PG_TEN ?
			R3_PAGE_TENS_DO_CARE :
			R3_PAGE_TENS_DO_NOT_CARE),

		UNITS_OF_PAGE(req->page) |
		(req->pagemask & PG_UNIT ?
			R3_PAGE_UNITS_DO_CARE :
			R3_PAGE_UNITS_DO_NOT_CARE),

		TENS_OF_HOUR(req->hour) |
		(req->pagemask & HR_TEN ?
			R3_HOURS_TENS_DO_CARE :
			R3_HOURS_TENS_DO_NOT_CARE),

		UNITS_OF_HOUR(req->hour) |
		(req->pagemask & HR_UNIT ?
			R3_HOURS_UNITS_DO_CARE :
			R3_HOURS_UNITS_DO_NOT_CARE),

		TENS_OF_MINUTE(req->minute) |
		(req->pagemask & MIN_TEN ?
			R3_MINUTES_TENS_DO_CARE :
			R3_MINUTES_TENS_DO_NOT_CARE),

		UNITS_OF_MINUTE(req->minute) |
		(req->pagemask & MIN_UNIT ?
			R3_MINUTES_UNITS_DO_CARE :
			R3_MINUTES_UNITS_DO_NOT_CARE),

		COMMAND_END) || i2c_senddata(t, SAA5246A_REGISTER_R2,

		R2_IN_R3_SELECT_PAGE_HUNDREDS |
		req->pgbuf << 4 |
		R2_BANK_0 |
		R2_HAMMING_CHECK_OFF,

		HUNDREDS_OF_PAGE(req->page) |
		R3_UPDATE_PAGE |
		(req->pagemask & PG_HUND ?
			R3_PAGE_HUNDREDS_DO_CARE :
			R3_PAGE_HUNDREDS_DO_NOT_CARE),

		COMMAND_END))
	{
		return -EIO;
	}

	t->is_searching[req->pgbuf] = true;
	return 0;
}
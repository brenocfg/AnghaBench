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
struct saa5246a_device {int* is_searching; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_END ; 
 int EINVAL ; 
 int EIO ; 
 unsigned char NUM_DAUS ; 
 unsigned char R2_BANK_0 ; 
 unsigned char R2_HAMMING_CHECK_OFF ; 
 unsigned char R2_IN_R3_SELECT_PAGE_HUNDREDS ; 
 int R3_HOLD_PAGE ; 
 int R3_PAGE_HUNDREDS_0 ; 
 int R3_PAGE_HUNDREDS_DO_NOT_CARE ; 
 int /*<<< orphan*/  SAA5246A_REGISTER_R2 ; 
 scalar_t__ i2c_senddata (struct saa5246a_device*,int /*<<< orphan*/ ,unsigned char,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int saa5246a_stop_dau(struct saa5246a_device *t,
    unsigned char dau_no)
{
	if (dau_no >= NUM_DAUS)
		return -EINVAL;
	if (i2c_senddata(t, SAA5246A_REGISTER_R2,

		R2_IN_R3_SELECT_PAGE_HUNDREDS |
		dau_no << 4 |
		R2_BANK_0 |
		R2_HAMMING_CHECK_OFF,

		R3_PAGE_HUNDREDS_0 |
		R3_HOLD_PAGE |
		R3_PAGE_HUNDREDS_DO_NOT_CARE,

		COMMAND_END))
	{
		return -EIO;
	}
	t->is_searching[dau_no] = false;
	return 0;
}
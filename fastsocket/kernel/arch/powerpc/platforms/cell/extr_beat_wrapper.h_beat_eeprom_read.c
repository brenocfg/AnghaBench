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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  BEAT_NVRW_CNT ; 
 int /*<<< orphan*/  HV_eeprom_read ; 
 int beat_hcall6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline s64 beat_eeprom_read(u64 index, u64 length, u8 *buffer)
{
	u64	b[6];
	s64	ret;

	if (length > BEAT_NVRW_CNT)
		return -1;
	ret = beat_hcall6(HV_eeprom_read, b, index, length);
	memcpy(buffer, b, length);
	return ret;
}
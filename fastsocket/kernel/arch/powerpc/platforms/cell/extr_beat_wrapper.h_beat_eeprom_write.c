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
typedef  scalar_t__ u64 ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 scalar_t__ BEAT_NVRW_CNT ; 
 int /*<<< orphan*/  HV_eeprom_write ; 
 int beat_hcall_norets8 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline s64 beat_eeprom_write(u64 index, u64 length, u8 *buffer)
{
	u64	b[6];

	if (length > BEAT_NVRW_CNT)
		return -1;
	memcpy(b, buffer, sizeof(b));
	return beat_hcall_norets8(HV_eeprom_write, index, length,
		b[0], b[1], b[2], b[3], b[4], b[5]);
}
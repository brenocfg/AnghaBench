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

/* Variables and functions */
 int /*<<< orphan*/  LM93_TEMP_OFFSET_MAX0 ; 
 int /*<<< orphan*/  LM93_TEMP_OFFSET_MAX1 ; 
 int /*<<< orphan*/  LM93_TEMP_OFFSET_MIN ; 
 int SENSORS_LIMIT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 LM93_TEMP_OFFSET_TO_REG(int off, int mode)
{
	int factor = mode ? 5 : 10;

	off = SENSORS_LIMIT(off, LM93_TEMP_OFFSET_MIN,
		mode ? LM93_TEMP_OFFSET_MAX1 : LM93_TEMP_OFFSET_MAX0);
	return (u8)((off + factor/2) / factor);
}
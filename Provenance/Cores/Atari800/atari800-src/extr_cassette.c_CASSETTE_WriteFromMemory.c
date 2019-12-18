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
typedef  int /*<<< orphan*/  UWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CASSETTE_TapeMotor (int) ; 
 int IMG_TAPE_WriteFromMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  cassette_file ; 
 scalar_t__ cassette_gapdelay ; 
 int /*<<< orphan*/  cassette_writable ; 

int CASSETTE_WriteFromMemory(UWORD src_addr, int length)
{
	int result;
	CASSETTE_TapeMotor(1);
	if (!cassette_writable)
		return 0;

	result = IMG_TAPE_WriteFromMemory(cassette_file, src_addr, length, cassette_gapdelay);
	cassette_gapdelay = 0;
	return result;
}
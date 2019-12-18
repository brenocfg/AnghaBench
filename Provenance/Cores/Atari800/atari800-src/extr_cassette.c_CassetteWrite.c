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

/* Variables and functions */
 int /*<<< orphan*/  IMG_TAPE_WriteAdvance (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cassette_file ; 
 scalar_t__ cassette_writable ; 

__attribute__((used)) static void CassetteWrite(int num_ticks)
{
	if (cassette_writable)
		IMG_TAPE_WriteAdvance(cassette_file, num_ticks);
}
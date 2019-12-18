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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int16_t ;

/* Variables and functions */

inline uint8_t BYTECLIP (
	int16_t val
)
{
	if (val < 0) val = 0;
	if (val > 255) val = 255;

	return (uint8_t)val;
}
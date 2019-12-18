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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfin_write_emudat (char) ; 

__attribute__((used)) static inline uint32_t bfin_write_emudat_chars(char a, char b, char c, char d)
{
	return bfin_write_emudat((a << 0) | (b << 8) | (c << 16) | (d << 24));
}
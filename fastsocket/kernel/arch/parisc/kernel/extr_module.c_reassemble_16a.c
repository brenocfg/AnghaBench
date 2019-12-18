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

__attribute__((used)) static inline int reassemble_16a(int as16)
{
	int s, t;

	/* Unusual 16-bit encoding, for wide mode only.  */
	t = (as16 << 1) & 0xffff;
	s = (as16 & 0x8000);
	return (t ^ s ^ (s >> 1)) | (s >> 15);
}
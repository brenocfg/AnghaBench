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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t cdfl_codec_blocksize(uint32_t bytes)
{
	/* determine FLAC block size, which must be 16-65535
	 * clamp to 2k since that's supposed to be the sweet spot */
	uint32_t hunkbytes = bytes / 4;
	while (hunkbytes > 2048)
		hunkbytes /= 2;
	return hunkbytes;
}
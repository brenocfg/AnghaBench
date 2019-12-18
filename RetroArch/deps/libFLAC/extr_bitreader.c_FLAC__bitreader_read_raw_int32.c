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
typedef  int FLAC__uint32 ;
typedef  int FLAC__int32 ;
typedef  int FLAC__bool ;
typedef  int /*<<< orphan*/  FLAC__BitReader ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint32 (int /*<<< orphan*/ *,int*,unsigned int) ; 

FLAC__bool FLAC__bitreader_read_raw_int32(FLAC__BitReader *br, FLAC__int32 *val, unsigned bits)
{
	FLAC__uint32 uval, mask;
	/* OPT: inline raw uint32 code here, or make into a macro if possible in the .h file */
	if(!FLAC__bitreader_read_raw_uint32(br, &uval, bits))
		return false;
	/* sign-extend *val assuming it is currently bits wide. */
	/* From: https://graphics.stanford.edu/~seander/bithacks.html#FixedSignExtend */
	mask = 1u << (bits - 1);
	*val = (uval ^ mask) - mask;
	return true;
}
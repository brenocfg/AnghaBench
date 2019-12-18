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
typedef  int /*<<< orphan*/  positions ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (short*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int jffs2_rtime_decompress(unsigned char *data_in,
				  unsigned char *cpage_out,
				  uint32_t srclen, uint32_t destlen,
				  void *model)
{
	short positions[256];
	int outpos = 0;
	int pos=0;

	memset(positions,0,sizeof(positions));

	while (outpos<destlen) {
		unsigned char value;
		int backoffs;
		int repeat;

		value = data_in[pos++];
		cpage_out[outpos++] = value; /* first the verbatim copied byte */
		repeat = data_in[pos++];
		backoffs = positions[value];

		positions[value]=outpos;
		if (repeat) {
			if (backoffs + repeat >= outpos) {
				while(repeat) {
					cpage_out[outpos++] = cpage_out[backoffs++];
					repeat--;
				}
			} else {
				memcpy(&cpage_out[outpos],&cpage_out[backoffs],repeat);
				outpos+=repeat;
			}
		}
	}
	return 0;
}
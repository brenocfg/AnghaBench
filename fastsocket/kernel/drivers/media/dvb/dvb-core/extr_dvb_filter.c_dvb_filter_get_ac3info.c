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
typedef  int u8 ;
struct dvb_audio_info {int off; int bit_rate; int frequency; int framesize; scalar_t__ layer; } ;

/* Variables and functions */
 int* ac3_bitrates ; 
 int** ac3_frames ; 
 int* freq ; 
 int /*<<< orphan*/  printk (char*,...) ; 

int dvb_filter_get_ac3info(u8 *mbuf, int count, struct dvb_audio_info *ai, int pr)
{
	u8 *headr;
	int found = 0;
	int c = 0;
	u8 frame = 0;
	int fr = 0;

	while ( !found  && c < count){
		u8 *b = mbuf+c;

		if ( b[0] == 0x0b &&  b[1] == 0x77 )
			found = 1;
		else {
			c++;
		}
	}

	if (!found) return -1;
	if (pr)
		printk("Audiostream: AC3");

	ai->off = c;
	if (c+5 >= count) return -1;

	ai->layer = 0;  // 0 for AC3
	headr = mbuf+c+2;

	frame = (headr[2]&0x3f);
	ai->bit_rate = ac3_bitrates[frame >> 1]*1000;

	if (pr)
		printk("  BRate: %d kb/s", (int) ai->bit_rate/1000);

	ai->frequency = (headr[2] & 0xc0 ) >> 6;
	fr = (headr[2] & 0xc0 ) >> 6;
	ai->frequency = freq[fr]*100;
	if (pr) printk ("  Freq: %d Hz\n", (int) ai->frequency);


	ai->framesize = ac3_frames[fr][frame >> 1];
	if ((frame & 1) &&  (fr == 1)) ai->framesize++;
	ai->framesize = ai->framesize << 1;
	if (pr) printk ("  Framesize %d\n",(int) ai->framesize);


	return 0;
}
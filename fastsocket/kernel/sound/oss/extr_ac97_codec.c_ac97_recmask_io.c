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
struct ac97_codec {unsigned int (* codec_read ) (struct ac97_codec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* codec_write ) (struct ac97_codec*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_RECORD_SELECT ; 
 unsigned int* ac97_oss_rm ; 
 int* ac97_rm2oss ; 
 unsigned int ffs (int) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 unsigned int stub1 (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int stub2 (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ac97_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ac97_recmask_io(struct ac97_codec *codec, int rw, int mask) 
{
	unsigned int val;

	if (rw) {
		/* read it from the card */
		val = codec->codec_read(codec, AC97_RECORD_SELECT);
#ifdef DEBUG
		printk("ac97_codec: ac97 recmask to set to 0x%04x\n", val);
#endif
		return (1 << ac97_rm2oss[val & 0x07]);
	}

	/* else, write the first set in the mask as the
	   output */	
	/* clear out current set value first (AC97 supports only 1 input!) */
	val = (1 << ac97_rm2oss[codec->codec_read(codec, AC97_RECORD_SELECT) & 0x07]);
	if (mask != val)
	    mask &= ~val;
       
	val = ffs(mask); 
	val = ac97_oss_rm[val-1];
	val |= val << 8;  /* set both channels */

#ifdef DEBUG
	printk("ac97_codec: setting ac97 recmask to 0x%04x\n", val);
#endif

	codec->codec_write(codec, AC97_RECORD_SELECT, val);

	return 0;
}
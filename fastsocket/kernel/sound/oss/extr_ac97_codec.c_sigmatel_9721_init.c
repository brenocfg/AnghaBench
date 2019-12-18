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
struct ac97_codec {scalar_t__ id; int /*<<< orphan*/  (* codec_write ) (struct ac97_codec*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* codec_read ) (struct ac97_codec*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_SIGMATEL_CIC1 ; 
 int /*<<< orphan*/  AC97_SIGMATEL_CIC2 ; 
 int /*<<< orphan*/  AC97_SIGMATEL_MULTICHN ; 
 int /*<<< orphan*/  AC97_SURROUND_MASTER ; 
 int /*<<< orphan*/  stub1 (struct ac97_codec*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  stub2 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sigmatel_9721_init(struct ac97_codec * codec)
{
	/* Only set up secondary codec */
	if (codec->id == 0)
		return 0;

	codec->codec_write(codec, AC97_SURROUND_MASTER, 0L);

	/* initialize SigmaTel STAC9721/23 as secondary codec, decoding AC link
	   sloc 3,4 = 0x01, slot 7,8 = 0x00, */
	codec->codec_write(codec, AC97_SIGMATEL_MULTICHN, 0x00);

	/* we don't have the crystal when we are on an AMR card, so use
	   BIT_CLK as our clock source. Write the magic word ABBA and read
	   back to enable register 0x78 */
	codec->codec_write(codec, AC97_SIGMATEL_CIC1, 0xabba);
	codec->codec_read(codec, AC97_SIGMATEL_CIC1);

	/* sync all the clocks*/
	codec->codec_write(codec, AC97_SIGMATEL_CIC2, 0x3802);

	return 0;
}
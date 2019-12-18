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
struct ac97_codec {int (* codec_read ) (struct ac97_codec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* codec_write ) (struct ac97_codec*,int /*<<< orphan*/ ,long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_MODEM_ID ; 
 int /*<<< orphan*/  AC97_RESET ; 
 int stub1 (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ac97_codec*,int /*<<< orphan*/ ,long) ; 
 int stub3 (struct ac97_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ac97_check_modem(struct ac97_codec *codec)
{
	/* Check for an AC97 1.0 soft modem (ID1) */
	if(codec->codec_read(codec, AC97_RESET) & 2)
		return 1;
	/* Check for an AC97 2.x soft modem */
	codec->codec_write(codec, AC97_EXTENDED_MODEM_ID, 0L);
	if(codec->codec_read(codec, AC97_EXTENDED_MODEM_ID) & 1)
		return 1;
	return 0;
}
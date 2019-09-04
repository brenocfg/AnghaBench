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
struct AVCodecTag {int dummy; } ;

/* Variables and functions */
 struct AVCodecTag const* ff_codec_wav_tags ; 

const struct AVCodecTag *avformat_get_riff_audio_tags(void)
{
    return ff_codec_wav_tags;
}
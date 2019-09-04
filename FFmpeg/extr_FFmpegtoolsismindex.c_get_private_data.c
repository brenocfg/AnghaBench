#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Track {int /*<<< orphan*/  codec_private; scalar_t__ codec_private_size; } ;
struct TYPE_3__ {scalar_t__ extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_mallocz (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int get_private_data(struct Track *track, AVCodecParameters *codecpar)
{
    track->codec_private_size = 0;
    track->codec_private      = av_mallocz(codecpar->extradata_size);
    if (!track->codec_private)
        return AVERROR(ENOMEM);
    track->codec_private_size = codecpar->extradata_size;
    memcpy(track->codec_private, codecpar->extradata, codecpar->extradata_size);
    return 0;
}
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
struct TYPE_3__ {int /*<<< orphan*/ * priv_data; } ;
typedef  int /*<<< orphan*/  OSSAudioData ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_oss_audio_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audio_write_trailer(AVFormatContext *s1)
{
    OSSAudioData *s = s1->priv_data;

    ff_oss_audio_close(s);
    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int mNumberChannelDescriptions; TYPE_1__* mChannelDescriptions; int /*<<< orphan*/  mChannelLayoutTag; } ;
struct TYPE_4__ {int mChannelLabel; } ;
typedef  TYPE_2__ AudioChannelLayout ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int get_channel_label (int) ; 
 int /*<<< orphan*/  kAudioChannelLayoutTag_UseChannelDescriptions ; 

__attribute__((used)) static int remap_layout(AudioChannelLayout *layout, uint64_t in_layout, int count)
{
    int i;
    int c = 0;
    layout->mChannelLayoutTag = kAudioChannelLayoutTag_UseChannelDescriptions;
    layout->mNumberChannelDescriptions = count;
    for (i = 0; i < count; i++) {
        int label;
        while (!(in_layout & (1 << c)) && c < 64)
            c++;
        if (c == 64)
            return AVERROR(EINVAL); // This should never happen
        label = get_channel_label(c);
        layout->mChannelDescriptions[i].mChannelLabel = label;
        if (label < 0)
            return AVERROR(EINVAL);
        c++;
    }
    return 0;
}
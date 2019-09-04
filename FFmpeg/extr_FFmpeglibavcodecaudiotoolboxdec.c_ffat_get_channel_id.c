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
typedef  scalar_t__ AudioChannelLabel ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CH_FRONT_CENTER ; 
 int /*<<< orphan*/  AV_CH_LOW_FREQUENCY_2 ; 
 int ff_ctzll (int /*<<< orphan*/ ) ; 
 scalar_t__ kAudioChannelLabel_CenterSurround ; 
 scalar_t__ kAudioChannelLabel_LFE2 ; 
 scalar_t__ kAudioChannelLabel_LFEScreen ; 
 scalar_t__ kAudioChannelLabel_Mono ; 
 scalar_t__ kAudioChannelLabel_RearSurroundLeft ; 
 scalar_t__ kAudioChannelLabel_RearSurroundRight ; 
 scalar_t__ kAudioChannelLabel_RightSurround ; 
 scalar_t__ kAudioChannelLabel_RightSurroundDirect ; 
 scalar_t__ kAudioChannelLabel_RightWide ; 
 scalar_t__ kAudioChannelLabel_TopBackRight ; 

__attribute__((used)) static int ffat_get_channel_id(AudioChannelLabel label)
{
    if (label == 0)
        return -1;
    else if (label <= kAudioChannelLabel_LFEScreen)
        return label - 1;
    else if (label <= kAudioChannelLabel_RightSurround)
        return label + 4;
    else if (label <= kAudioChannelLabel_CenterSurround)
        return label + 1;
    else if (label <= kAudioChannelLabel_RightSurroundDirect)
        return label + 23;
    else if (label <= kAudioChannelLabel_TopBackRight)
        return label - 1;
    else if (label < kAudioChannelLabel_RearSurroundLeft)
        return -1;
    else if (label <= kAudioChannelLabel_RearSurroundRight)
        return label - 29;
    else if (label <= kAudioChannelLabel_RightWide)
        return label - 4;
    else if (label == kAudioChannelLabel_LFE2)
        return ff_ctzll(AV_CH_LOW_FREQUENCY_2);
    else if (label == kAudioChannelLabel_Mono)
        return ff_ctzll(AV_CH_FRONT_CENTER);
    else
        return -1;
}
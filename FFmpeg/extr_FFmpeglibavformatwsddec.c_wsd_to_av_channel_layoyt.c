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
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AV_CH_BACK_CENTER ; 
 int AV_CH_BACK_LEFT ; 
 int AV_CH_BACK_RIGHT ; 
 int AV_CH_FRONT_CENTER ; 
 int AV_CH_FRONT_LEFT ; 
 int AV_CH_FRONT_LEFT_OF_CENTER ; 
 int AV_CH_FRONT_RIGHT ; 
 int AV_CH_FRONT_RIGHT_OF_CENTER ; 
 int AV_CH_LOW_FREQUENCY ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int wsd_to_av_channel_layoyt(AVFormatContext *s, int bit)
{
    switch (bit) {
    case 2: return AV_CH_BACK_RIGHT;
    case 3:
        avpriv_request_sample(s, "Rr-middle");
        break;
    case 4: return AV_CH_BACK_CENTER;
    case 5:
        avpriv_request_sample(s, "Lr-middle");
        break;
    case 6: return AV_CH_BACK_LEFT;
    case 24: return AV_CH_LOW_FREQUENCY;
    case 26: return AV_CH_FRONT_RIGHT;
    case 27: return AV_CH_FRONT_RIGHT_OF_CENTER;
    case 28: return AV_CH_FRONT_CENTER;
    case 29: return AV_CH_FRONT_LEFT_OF_CENTER;
    case 30: return AV_CH_FRONT_LEFT;
    default:
        av_log(s, AV_LOG_WARNING, "reserved channel assignment\n");
        break;
    }
    return 0;
}
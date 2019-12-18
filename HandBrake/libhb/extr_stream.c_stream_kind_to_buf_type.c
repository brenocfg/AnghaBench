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

/* Variables and functions */
#define  A 130 
 int AUDIO_BUF ; 
 int OTHER_BUF ; 
#define  S 129 
 int SUBTITLE_BUF ; 
#define  V 128 
 int VIDEO_BUF ; 

__attribute__((used)) static int stream_kind_to_buf_type(int kind)
{
    switch (kind)
    {
        case A:
            return AUDIO_BUF;
        case V:
            return VIDEO_BUF;
        case S:
            return SUBTITLE_BUF;
        default:
            return OTHER_BUF;
    }
}
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
typedef  enum AVChromaLocation { ____Placeholder_AVChromaLocation } AVChromaLocation ;

/* Variables and functions */
 int AVCHROMA_LOC_NB ; 
 int AVCHROMA_LOC_UNSPECIFIED ; 
 scalar_t__ avcodec_enum_to_chroma_pos (int*,int*,int) ; 

enum AVChromaLocation avcodec_chroma_pos_to_enum(int xpos, int ypos)
{
    int pos, xout, yout;

    for (pos = AVCHROMA_LOC_UNSPECIFIED + 1; pos < AVCHROMA_LOC_NB; pos++) {
        if (avcodec_enum_to_chroma_pos(&xout, &yout, pos) == 0 && xout == xpos && yout == ypos)
            return pos;
    }
    return AVCHROMA_LOC_UNSPECIFIED;
}
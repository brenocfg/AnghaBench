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
#define  AVCHROMA_LOC_BOTTOM 134 
#define  AVCHROMA_LOC_BOTTOMLEFT 133 
#define  AVCHROMA_LOC_CENTER 132 
#define  AVCHROMA_LOC_LEFT 131 
#define  AVCHROMA_LOC_TOP 130 
#define  AVCHROMA_LOC_TOPLEFT 129 
#define  AVCHROMA_LOC_UNSPECIFIED 128 
 int ZIMG_CHROMA_BOTTOM ; 
 int ZIMG_CHROMA_BOTTOM_LEFT ; 
 int ZIMG_CHROMA_CENTER ; 
 int ZIMG_CHROMA_LEFT ; 
 int ZIMG_CHROMA_TOP ; 
 int ZIMG_CHROMA_TOP_LEFT ; 

__attribute__((used)) static int convert_chroma_location(enum AVChromaLocation chroma_location)
{
    switch (chroma_location) {
    case AVCHROMA_LOC_UNSPECIFIED:
    case AVCHROMA_LOC_LEFT:
        return ZIMG_CHROMA_LEFT;
    case AVCHROMA_LOC_CENTER:
        return ZIMG_CHROMA_CENTER;
    case AVCHROMA_LOC_TOPLEFT:
        return ZIMG_CHROMA_TOP_LEFT;
    case AVCHROMA_LOC_TOP:
        return ZIMG_CHROMA_TOP;
    case AVCHROMA_LOC_BOTTOMLEFT:
        return ZIMG_CHROMA_BOTTOM_LEFT;
    case AVCHROMA_LOC_BOTTOM:
        return ZIMG_CHROMA_BOTTOM;
    }
    return ZIMG_CHROMA_LEFT;
}
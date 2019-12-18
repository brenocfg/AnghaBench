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
typedef  int /*<<< orphan*/  RaChromaSamplePosition ;

/* Variables and functions */
#define  AVCHROMA_LOC_LEFT 129 
#define  AVCHROMA_LOC_TOPLEFT 128 
 int /*<<< orphan*/  RA_CHROMA_SAMPLE_POSITION_COLOCATED ; 
 int /*<<< orphan*/  RA_CHROMA_SAMPLE_POSITION_UNKNOWN ; 
 int /*<<< orphan*/  RA_CHROMA_SAMPLE_POSITION_VERTICAL ; 

__attribute__((used)) static inline RaChromaSamplePosition chroma_loc_map(enum AVChromaLocation chroma_loc)
{
    switch (chroma_loc) {
    case AVCHROMA_LOC_LEFT:
        return RA_CHROMA_SAMPLE_POSITION_VERTICAL;
    case AVCHROMA_LOC_TOPLEFT:
        return RA_CHROMA_SAMPLE_POSITION_COLOCATED;
    default:
        return RA_CHROMA_SAMPLE_POSITION_UNKNOWN;
    }
}
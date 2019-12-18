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
typedef  int SegmentType ;

/* Variables and functions */
#define  SEGMENT_TYPE_MP4 129 
#define  SEGMENT_TYPE_WEBM 128 

__attribute__((used)) static const char *get_extension_str(SegmentType type, int single_file)
{
    switch (type) {

    case SEGMENT_TYPE_MP4:  return single_file ? "mp4" : "m4s";
    case SEGMENT_TYPE_WEBM: return "webm";
    default: return NULL;
    }
}
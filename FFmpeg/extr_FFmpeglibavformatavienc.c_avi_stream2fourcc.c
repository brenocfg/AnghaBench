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
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;

/* Variables and functions */
 int AVMEDIA_TYPE_SUBTITLE ; 
 int AVMEDIA_TYPE_VIDEO ; 

__attribute__((used)) static char *avi_stream2fourcc(char *tag, int index, enum AVMediaType type)
{
    tag[0] = '0' + index / 10;
    tag[1] = '0' + index % 10;
    if (type == AVMEDIA_TYPE_VIDEO) {
        tag[2] = 'd';
        tag[3] = 'c';
    } else if (type == AVMEDIA_TYPE_SUBTITLE) {
        // note: this is not an official code
        tag[2] = 's';
        tag[3] = 'b';
    } else {
        tag[2] = 'w';
        tag[3] = 'b';
    }
    tag[4] = '\0';
    return tag;
}
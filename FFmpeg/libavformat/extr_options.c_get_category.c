#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ iformat; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVClassCategory ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CLASS_CATEGORY_DEMUXER ; 
 int /*<<< orphan*/  AV_CLASS_CATEGORY_MUXER ; 

__attribute__((used)) static AVClassCategory get_category(void *ptr)
{
    AVFormatContext* s = ptr;
    if(s->iformat) return AV_CLASS_CATEGORY_DEMUXER;
    else           return AV_CLASS_CATEGORY_MUXER;
}
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
struct AVFormatContext {TYPE_1__* oformat; } ;
typedef  enum AVAppToDevMessageType { ____Placeholder_AVAppToDevMessageType } AVAppToDevMessageType ;
struct TYPE_2__ {int (* control_message ) (struct AVFormatContext*,int,void*,size_t) ;} ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int stub1 (struct AVFormatContext*,int,void*,size_t) ; 

int avdevice_app_to_dev_control_message(struct AVFormatContext *s, enum AVAppToDevMessageType type,
                                        void *data, size_t data_size)
{
    if (!s->oformat || !s->oformat->control_message)
        return AVERROR(ENOSYS);
    return s->oformat->control_message(s, type, data, data_size);
}
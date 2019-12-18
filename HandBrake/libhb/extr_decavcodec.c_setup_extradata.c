#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
struct TYPE_11__ {TYPE_3__ packet_info; int /*<<< orphan*/  context; TYPE_2__* parser; } ;
typedef  TYPE_4__ hb_work_private_t ;
struct TYPE_12__ {int extradata_size; int /*<<< orphan*/ * extradata; } ;
struct TYPE_9__ {TYPE_1__* parser; } ;
struct TYPE_8__ {int (* split ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/ * av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_extradata( hb_work_private_t * pv, AVCodecContext * context )
{
    // we can't call the avstream funcs but the read_header func in the
    // AVInputFormat may set up some state in the AVContext. In particular
    // vc1t_read_header allocates 'extradata' to deal with header issues
    // related to Microsoft's bizarre engineering notions. We alloc a chunk
    // of space to make vc1 work then associate the codec with the context.
    if (context->extradata == NULL)
    {
        if (pv->parser == NULL || pv->parser->parser == NULL ||
            pv->parser->parser->split == NULL)
        {
            return 0;
        }
        else
        {
            int size;
            size = pv->parser->parser->split(pv->context, pv->packet_info.data,
                                             pv->packet_info.size);
            if (size > 0)
            {
                context->extradata_size = size;
                context->extradata =
                                av_malloc(size + AV_INPUT_BUFFER_PADDING_SIZE);
                if (context->extradata == NULL)
                    return 1;
                memcpy(context->extradata, pv->packet_info.data, size);
                return 0;
            }
        }
        return 1;
    }

    return 0;
}
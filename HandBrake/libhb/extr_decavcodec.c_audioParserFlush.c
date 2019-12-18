#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {int size; int /*<<< orphan*/  pts; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {TYPE_4__ packet_info; TYPE_5__* parser; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ hb_work_private_t ;
struct TYPE_8__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_work_object_t ;
struct TYPE_10__ {int /*<<< orphan*/  pts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_parser_parse2 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decodeAudio (TYPE_1__*,TYPE_4__*) ; 

__attribute__((used)) static void audioParserFlush(hb_work_object_t * w)
{
    hb_work_private_t * pv = w->private_data;
    uint8_t * pout = NULL;
    int       pout_len = 0;
    int64_t   parser_pts = AV_NOPTS_VALUE;

    do
    {
        if (pv->parser)
        {
            av_parser_parse2(pv->parser, pv->context, &pout, &pout_len,
                                   NULL, 0,
                                   AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0 );
            parser_pts = pv->parser->pts;
        }

        if (pout != NULL && pout_len > 0)
        {
            pv->packet_info.data         = pout;
            pv->packet_info.size         = pout_len;
            pv->packet_info.pts          = parser_pts;

            decodeAudio(pv, &pv->packet_info);
        }
    } while (pout != NULL && pout_len > 0);
}
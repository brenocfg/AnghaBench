#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct AVCodecParserContext {int dummy; } ;
struct TYPE_3__ {struct AVCodecParserContext* parser; } ;
typedef  TYPE_1__ AVStream ;

/* Variables and functions */

struct AVCodecParserContext *av_stream_get_parser(const AVStream *st)
{
    return st->parser;
}
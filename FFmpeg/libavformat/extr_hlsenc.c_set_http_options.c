#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  url; } ;
struct TYPE_5__ {char* method; char* user_agent; int timeout; char* headers; scalar_t__ http_persistent; } ;
typedef  TYPE_1__ HLSContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ ) ; 
 int ff_is_http_proto (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_http_options(AVFormatContext *s, AVDictionary **options, HLSContext *c)
{
    int http_base_proto = ff_is_http_proto(s->url);

    if (c->method) {
        av_dict_set(options, "method", c->method, 0);
    } else if (http_base_proto) {
        av_dict_set(options, "method", "PUT", 0);
    }
    if (c->user_agent)
        av_dict_set(options, "user_agent", c->user_agent, 0);
    if (c->http_persistent)
        av_dict_set_int(options, "multiple_requests", 1, 0);
    if (c->timeout >= 0)
        av_dict_set_int(options, "timeout", c->timeout, 0);
    if (c->headers)
        av_dict_set(options, "headers", c->headers, 0);
}
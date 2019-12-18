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
struct TYPE_5__ {size_t pre_parsed; int paused; } ;
typedef  TYPE_1__ parser_data_t ;
struct TYPE_6__ {scalar_t__ data; } ;
typedef  TYPE_2__ http_parser ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  http_parser_pause (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t continue_parsing(http_parser *parser, size_t length)
{
    parser_data_t *data = (parser_data_t *) parser->data;

    /* Part of the received data may have been parsed earlier
     * so we must skip that before parsing resumes */
    length = MIN(length, data->pre_parsed);
    data->pre_parsed -= length;
    ESP_LOGD(TAG, LOG_FMT("skip pre-parsed data of size = %d"), length);

    http_parser_pause(parser, 0);
    data->paused = false;
    ESP_LOGD(TAG, LOG_FMT("un-paused"));
    return length;
}
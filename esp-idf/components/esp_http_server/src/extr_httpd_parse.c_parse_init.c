#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  on_message_complete; int /*<<< orphan*/  on_body; int /*<<< orphan*/  on_headers_complete; int /*<<< orphan*/  on_header_value; int /*<<< orphan*/  on_header_field; int /*<<< orphan*/  on_url; } ;
struct TYPE_8__ {TYPE_6__ settings; int /*<<< orphan*/ * req; } ;
typedef  TYPE_1__ parser_data_t ;
typedef  int /*<<< orphan*/  httpd_req_t ;
struct TYPE_9__ {void* data; } ;
typedef  TYPE_2__ http_parser ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_REQUEST ; 
 int /*<<< orphan*/  cb_header_field ; 
 int /*<<< orphan*/  cb_header_value ; 
 int /*<<< orphan*/  cb_headers_complete ; 
 int /*<<< orphan*/  cb_no_body ; 
 int /*<<< orphan*/  cb_on_body ; 
 int /*<<< orphan*/  cb_url ; 
 int /*<<< orphan*/  http_parser_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_parser_settings_init (TYPE_6__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void parse_init(httpd_req_t *r, http_parser *parser, parser_data_t *data)
{
    /* Initialize parser data */
    memset(data, 0, sizeof(parser_data_t));
    data->req = r;

    /* Initialize parser */
    http_parser_init(parser, HTTP_REQUEST);
    parser->data = (void *)data;

    /* Initialize parser settings */
    http_parser_settings_init(&data->settings);

    /* Set parser callbacks */
    data->settings.on_url              = cb_url;
    data->settings.on_header_field     = cb_header_field;
    data->settings.on_header_value     = cb_header_value;
    data->settings.on_headers_complete = cb_headers_complete;
    data->settings.on_body             = cb_on_body;
    data->settings.on_message_complete = cb_no_body;
}
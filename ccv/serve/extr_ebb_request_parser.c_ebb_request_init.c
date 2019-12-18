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
struct TYPE_3__ {char* multipart_boundary; int keep_alive; int /*<<< orphan*/ * on_query_string; int /*<<< orphan*/ * on_path; int /*<<< orphan*/ * on_fragment; int /*<<< orphan*/ * on_uri; int /*<<< orphan*/ * on_header_value; int /*<<< orphan*/ * on_header_field; int /*<<< orphan*/ * on_part_data; int /*<<< orphan*/ * on_part_data_complete; int /*<<< orphan*/ * on_multipart_header_value; int /*<<< orphan*/ * on_multipart_header_field; int /*<<< orphan*/ * on_multipart_headers_complete; int /*<<< orphan*/ * on_body; int /*<<< orphan*/ * on_headers_complete; int /*<<< orphan*/ * on_complete; scalar_t__ multipart_boundary_len; scalar_t__ number_of_multipart_headers; int /*<<< orphan*/  transfer_encoding; scalar_t__ number_of_headers; scalar_t__ version_minor; scalar_t__ version_major; scalar_t__ content_length; scalar_t__ body_read; scalar_t__ eating_body; int /*<<< orphan*/  expect_continue; } ;
typedef  TYPE_1__ ebb_request ;

/* Variables and functions */
 int /*<<< orphan*/  EBB_IDENTITY ; 
 int /*<<< orphan*/  FALSE ; 

void ebb_request_init(ebb_request *request)
{
  request->expect_continue = FALSE;
  request->eating_body = 0;
  request->body_read = 0;
  request->content_length = 0;
  request->version_major = 0;
  request->version_minor = 0;
  request->number_of_headers = 0;
  request->transfer_encoding = EBB_IDENTITY;
  request->number_of_multipart_headers = 0;
  request->multipart_boundary_len = 0;
  request->multipart_boundary[0] = request->multipart_boundary[1] = '-';
  request->keep_alive = -1;

  request->on_complete = NULL;
  request->on_headers_complete = NULL;
  request->on_body = NULL;
  request->on_multipart_headers_complete = NULL;
  request->on_multipart_header_field = NULL;
  request->on_multipart_header_value = NULL;
  request->on_part_data_complete = NULL;
  request->on_part_data = NULL;
  request->on_header_field = NULL;
  request->on_header_value = NULL;
  request->on_uri = NULL;
  request->on_fragment = NULL;
  request->on_path = NULL;
  request->on_query_string = NULL;
}
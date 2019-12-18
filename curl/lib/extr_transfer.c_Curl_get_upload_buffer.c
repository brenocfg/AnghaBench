#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ulbuf; } ;
struct TYPE_3__ {int /*<<< orphan*/  upload_buffer_size; } ;
struct Curl_easy {TYPE_2__ state; TYPE_1__ set; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 

CURLcode Curl_get_upload_buffer(struct Curl_easy *data)
{
  if(!data->state.ulbuf) {
    data->state.ulbuf = malloc(data->set.upload_buffer_size);
    if(!data->state.ulbuf)
      return CURLE_OUT_OF_MEMORY;
  }
  return CURLE_OK;
}
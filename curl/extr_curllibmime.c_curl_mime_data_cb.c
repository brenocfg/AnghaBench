#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  curl_seek_callback ;
typedef  scalar_t__ curl_read_callback ;
typedef  int /*<<< orphan*/  curl_off_t ;
struct TYPE_4__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  datasize; void* arg; int /*<<< orphan*/  freefunc; int /*<<< orphan*/  seekfunc; scalar_t__ readfunc; } ;
typedef  TYPE_1__ curl_mimepart ;
typedef  int /*<<< orphan*/  curl_free_callback ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_BAD_FUNCTION_ARGUMENT ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  MIMEKIND_CALLBACK ; 
 int /*<<< orphan*/  cleanup_part_content (TYPE_1__*) ; 

CURLcode curl_mime_data_cb(curl_mimepart *part, curl_off_t datasize,
                           curl_read_callback readfunc,
                           curl_seek_callback seekfunc,
                           curl_free_callback freefunc, void *arg)
{
  if(!part)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  cleanup_part_content(part);

  if(readfunc) {
    part->readfunc = readfunc;
    part->seekfunc = seekfunc;
    part->freefunc = freefunc;
    part->arg = arg;
    part->datasize = datasize;
    part->kind = MIMEKIND_CALLBACK;
  }

  return CURLE_OK;
}
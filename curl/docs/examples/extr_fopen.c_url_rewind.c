#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  curl; int /*<<< orphan*/  file; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  buffer_len; int /*<<< orphan*/  buffer_pos; int /*<<< orphan*/ * buffer; TYPE_1__ handle; } ;
typedef  TYPE_2__ URL_FILE ;

/* Variables and functions */
#define  CFTYPE_CURL 129 
#define  CFTYPE_FILE 128 
 int /*<<< orphan*/  curl_multi_add_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_handle ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 

void url_rewind(URL_FILE *file)
{
  switch(file->type) {
  case CFTYPE_FILE:
    rewind(file->handle.file); /* passthrough */
    break;

  case CFTYPE_CURL:
    /* halt transaction */
    curl_multi_remove_handle(multi_handle, file->handle.curl);

    /* restart */
    curl_multi_add_handle(multi_handle, file->handle.curl);

    /* ditch buffer - write will recreate - resets stream pos*/
    free(file->buffer);
    file->buffer = NULL;
    file->buffer_pos = 0;
    file->buffer_len = 0;

    break;

  default: /* unknown or supported type - oh dear */
    break;
  }
}
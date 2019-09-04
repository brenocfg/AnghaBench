#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* img; } ;
typedef  TYPE_2__ zbar_src_mgr_t ;
struct TYPE_8__ {int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ zbar_image_t ;
typedef  TYPE_4__* j_decompress_ptr ;
struct TYPE_9__ {TYPE_1__* src; } ;
struct TYPE_6__ {int /*<<< orphan*/  bytes_in_buffer; int /*<<< orphan*/  next_input_byte; } ;

/* Variables and functions */

void init_source (j_decompress_ptr cinfo)
{
    /* buffer/length refer to compressed data */
    /* FIXME find img */
    const zbar_image_t *img = ((zbar_src_mgr_t*)cinfo->src)->img;
    cinfo->src->next_input_byte = img->data;
    cinfo->src->bytes_in_buffer = img->datalen;
}
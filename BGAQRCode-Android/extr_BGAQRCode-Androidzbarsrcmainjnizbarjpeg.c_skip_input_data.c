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
typedef  TYPE_2__* j_decompress_ptr ;
struct TYPE_6__ {TYPE_1__* src; } ;
struct TYPE_5__ {long bytes_in_buffer; long next_input_byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_input_buffer (TYPE_2__*) ; 

void skip_input_data (j_decompress_ptr cinfo,
                      long num_bytes)
{
    if(num_bytes > 0) {
        if (num_bytes < cinfo->src->bytes_in_buffer) {
            cinfo->src->next_input_byte += num_bytes;
            cinfo->src->bytes_in_buffer -= num_bytes;
        }
        else {
            fill_input_buffer(cinfo);
        }
    }
}
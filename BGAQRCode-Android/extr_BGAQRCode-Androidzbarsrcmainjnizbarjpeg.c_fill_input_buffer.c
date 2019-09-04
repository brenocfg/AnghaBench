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
typedef  TYPE_2__* j_decompress_ptr ;
struct TYPE_5__ {TYPE_1__* src; } ;
struct TYPE_4__ {int bytes_in_buffer; int /*<<< orphan*/  next_input_byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  fake_eoi ; 

int fill_input_buffer (j_decompress_ptr cinfo)
{
    /* buffer underrun error case */
    cinfo->src->next_input_byte = fake_eoi;
    cinfo->src->bytes_in_buffer = 2;
    return(1);
}
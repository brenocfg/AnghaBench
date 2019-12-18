#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ide_device {int* data_ptr; int* data_end; int* io_buffer; } ;

/* Variables and functions */
 scalar_t__ count ; 

__attribute__((used)) static void ide_dummy_transfer_stop(struct ide_device *s) {
    s->data_ptr = s->data_end = s->io_buffer;
    s->io_buffer[0] = s->io_buffer[1] = 
    s->io_buffer[2] = s->io_buffer[3] = 0xff;
    count = 0;
}
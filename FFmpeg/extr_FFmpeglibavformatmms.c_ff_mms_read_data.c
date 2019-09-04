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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int remaining_in_len; int read_in_ptr; } ;
typedef  TYPE_1__ MMSContext ;

/* Variables and functions */
 int FFMIN (int const,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int,int) ; 

int ff_mms_read_data(MMSContext *mms, uint8_t *buf, const int size)
{
    int read_size;
    read_size = FFMIN(size, mms->remaining_in_len);
    memcpy(buf, mms->read_in_ptr, read_size);
    mms->remaining_in_len -= read_size;
    mms->read_in_ptr      += read_size;
    return read_size;
}
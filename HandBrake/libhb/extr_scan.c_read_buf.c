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
typedef  int /*<<< orphan*/  hb_stream_t ;
struct TYPE_3__ {scalar_t__ dvd; scalar_t__ bd; } ;
typedef  TYPE_1__ hb_scan_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_bd_read (scalar_t__) ; 
 int /*<<< orphan*/ * hb_dvd_read (scalar_t__) ; 
 int /*<<< orphan*/ * hb_stream_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static hb_buffer_t * read_buf(hb_scan_t * data, hb_stream_t * stream)
{
    if (data->bd)
    {
        return hb_bd_read(data->bd);
    }
    else if (data->dvd)
    {
        return hb_dvd_read(data->dvd);
    }
    else if (stream)
    {
        return hb_stream_read(stream);
    }

    // This shouldn't happen
    return NULL;
}
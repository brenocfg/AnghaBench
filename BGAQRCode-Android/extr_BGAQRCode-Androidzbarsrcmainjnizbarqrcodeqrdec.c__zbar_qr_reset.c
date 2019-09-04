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
struct TYPE_5__ {TYPE_1__* finder_lines; } ;
typedef  TYPE_2__ qr_reader ;
struct TYPE_4__ {scalar_t__ nlines; } ;

/* Variables and functions */

void _zbar_qr_reset (qr_reader *reader)
{
    reader->finder_lines[0].nlines = 0;
    reader->finder_lines[1].nlines = 0;
}
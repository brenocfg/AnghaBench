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
struct TYPE_3__ {scalar_t__ buffer_position; int /*<<< orphan*/  buffer; scalar_t__ buffer_count; } ;
typedef  TYPE_1__ png_modifier ;

/* Variables and functions */
 int /*<<< orphan*/  modifier_crc (int /*<<< orphan*/ ) ; 
 scalar_t__ png_get_uint_32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
modifier_setbuffer(png_modifier *pm)
{
   modifier_crc(pm->buffer);
   pm->buffer_count = png_get_uint_32(pm->buffer)+12;
   pm->buffer_position = 0;
}
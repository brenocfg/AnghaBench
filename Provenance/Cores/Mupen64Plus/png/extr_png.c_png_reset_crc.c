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
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
struct TYPE_3__ {scalar_t__ crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_NULL ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_reset_crc(png_structrp png_ptr)
{
   /* The cast is safe because the crc is a 32-bit value. */
   png_ptr->crc = (png_uint_32)crc32(0, Z_NULL, 0);
}
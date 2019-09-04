#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* paint_char ) (unsigned int,unsigned int,unsigned char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int* gc_buffer_attributes ; 
 unsigned char* gc_buffer_characters ; 
 int /*<<< orphan*/ * gc_buffer_colorcodes ; 
 unsigned int gc_buffer_columns ; 
 unsigned int gc_buffer_rows ; 
 int /*<<< orphan*/  gc_color_code ; 
 TYPE_1__ gc_ops ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned int,unsigned char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gc_paint_char(unsigned int xx, unsigned int yy, unsigned char ch, int attrs)
{
	if ( xx < gc_buffer_columns && yy < gc_buffer_rows )
	{
		uint32_t index = (yy * gc_buffer_columns) + xx;
 
		gc_buffer_attributes[index] = attrs;
		gc_buffer_characters[index] = ch;
		gc_buffer_colorcodes[index] = gc_color_code;
	}

	gc_ops.paint_char(xx, yy, ch, attrs, 0, 0);
}
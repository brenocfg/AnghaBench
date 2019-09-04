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
struct TYPE_2__ {int /*<<< orphan*/  (* show_cursor ) (unsigned int,unsigned int) ;int /*<<< orphan*/  (* paint_char ) (unsigned int,unsigned int,unsigned char,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_CODE_GET (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned char* gc_buffer_attributes ; 
 unsigned char* gc_buffer_characters ; 
 unsigned char* gc_buffer_colorcodes ; 
 unsigned int gc_buffer_columns ; 
 unsigned int gc_buffer_rows ; 
 unsigned char gc_color_code ; 
 TYPE_1__ gc_ops ; 
 int /*<<< orphan*/  gc_update_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned int,unsigned char,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (unsigned int,unsigned int) ; 

__attribute__((used)) static void
gc_show_cursor(unsigned int xx, unsigned int yy)
{
	if ( xx < gc_buffer_columns && yy < gc_buffer_rows )
	{
		uint32_t index = (yy * gc_buffer_columns) + xx;
		unsigned char attribute = gc_buffer_attributes[index];
		unsigned char character = gc_buffer_characters[index];
		unsigned char colorcode = gc_buffer_colorcodes[index];
		unsigned char colorcodesave = gc_color_code;

		gc_update_color(COLOR_CODE_GET(colorcode, FALSE), TRUE );
		gc_update_color(COLOR_CODE_GET(colorcode, TRUE ), FALSE);

		gc_ops.paint_char(xx, yy, character, attribute, 0, 0);

		gc_update_color(COLOR_CODE_GET(colorcodesave, TRUE ), TRUE );
		gc_update_color(COLOR_CODE_GET(colorcodesave, FALSE), FALSE);
	}
	else
	{
		gc_ops.show_cursor(xx, yy);
	}
}
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
struct TYPE_3__ {int cursor_row; int /*<<< orphan*/  con_cols; int /*<<< orphan*/  cursor_col; } ;
typedef  TYPE_1__ console_data_s ;

/* Variables and functions */
 int /*<<< orphan*/  __console_clear_line (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* curr_con ; 

__attribute__((used)) static void __console_clear_to_cursor() {
	console_data_s *con;
	int cur_row;

  if( !(con = curr_con) ) return;
	cur_row = con->cursor_row;

  __console_clear_line( cur_row, 0, con->cursor_col );

  while( cur_row-- )
    __console_clear_line( cur_row, 0, con->con_cols );
}
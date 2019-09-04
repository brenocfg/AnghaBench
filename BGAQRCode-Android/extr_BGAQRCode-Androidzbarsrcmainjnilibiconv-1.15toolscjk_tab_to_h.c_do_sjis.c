#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int rows; int cols; char* check_row_expr; char* check_col_expr; char* byte_row_expr; char* byte_col_expr; int /*<<< orphan*/  byte_col; int /*<<< orphan*/  byte_row; int /*<<< orphan*/  col_byte; int /*<<< orphan*/  row_byte; } ;
typedef  TYPE_1__ Encoding ;

/* Variables and functions */
 int /*<<< orphan*/  byte_col_sjis ; 
 int /*<<< orphan*/  byte_row_sjis ; 
 int /*<<< orphan*/  col_byte_sjis ; 
 int /*<<< orphan*/  invert (TYPE_1__*) ; 
 int /*<<< orphan*/  output_charset2uni (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  output_uni2charset_sparse (char const*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  read_table (TYPE_1__*) ; 
 int /*<<< orphan*/  row_byte_sjis ; 

__attribute__((used)) static void do_sjis (const char* name)
{
  Encoding enc;

  enc.rows = 94;
  enc.cols = 188;
  enc.row_byte = row_byte_sjis;
  enc.col_byte = col_byte_sjis;
  enc.byte_row = byte_row_sjis;
  enc.byte_col = byte_col_sjis;
  enc.check_row_expr = "(%1$s >= 0x81 && %1$s < 0xa0) || (%1$s >= 0xe0)";
  enc.check_col_expr = "(%1$s >= 0x40 && %1$s < 0x7f) || (%1$s >= 0x80 && %1$s < 0xfd)";
  enc.byte_row_expr = "%1$s - (%1$s >= 0xe0 ? 0xc1 : 0x81)";
  enc.byte_col_expr = "%1$s - (%1$s >= 0x80 ? 0x41 : 0x40)";

  read_table(&enc);
  output_charset2uni(name,&enc);
  invert(&enc); output_uni2charset_sparse(name,&enc,false);
}
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
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  field_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIGCHAR_WIDTH ; 
 int /*<<< orphan*/  Field_VariableSizeDraw (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Field_BigDraw( field_t *edit, int x, int y, int width, qboolean showCursor ) 
{
	Field_VariableSizeDraw( edit, x, y, width, BIGCHAR_WIDTH, showCursor );
}
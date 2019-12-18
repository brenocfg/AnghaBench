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
struct TYPE_3__ {int /*<<< orphan*/  image; int /*<<< orphan*/  buffer; int /*<<< orphan*/  store; } ;
typedef  TYPE_1__ YuiVdp1 ;

/* Variables and functions */
 int /*<<< orphan*/  YUI_VIEWER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_text_buffer_set_text (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  yui_viewer_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_vdp1_clear(YuiVdp1 * vdp1) {
	gtk_list_store_clear(vdp1->store);
	gtk_text_buffer_set_text(vdp1->buffer, "", -1);
	yui_viewer_clear(YUI_VIEWER(vdp1->image));
}
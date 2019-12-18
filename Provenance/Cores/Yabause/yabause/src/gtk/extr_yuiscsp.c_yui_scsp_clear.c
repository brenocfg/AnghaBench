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
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ YuiScsp ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_text_buffer_set_text (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void yui_scsp_clear(YuiScsp * scsp) {
	gtk_text_buffer_set_text(scsp->buffer, "", -1);
}
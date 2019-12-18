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
typedef  int /*<<< orphan*/  YuiWindow ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YUI_SH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_sh_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_ssh ; 

GtkWidget * yui_ssh_new(YuiWindow * y) { 
  return GTK_WIDGET( yui_ssh = YUI_SH(yui_sh_new( y, FALSE )) );
}
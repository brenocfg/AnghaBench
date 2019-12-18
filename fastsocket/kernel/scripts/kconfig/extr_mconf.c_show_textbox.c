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

/* Variables and functions */
 int /*<<< orphan*/  dialog_clear () ; 
 int /*<<< orphan*/  dialog_textbox (char const*,char const*,int,int) ; 

__attribute__((used)) static void show_textbox(const char *title, const char *text, int r, int c)
{
	dialog_clear();
	dialog_textbox(title, text, r, c);
}
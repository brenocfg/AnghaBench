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
struct vc_data {int vc_y; int vc_top; int vc_x; scalar_t__ vc_decom; } ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  respond_string (char*,struct tty_struct*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static void cursor_report(struct vc_data *vc, struct tty_struct *tty)
{
	char buf[40];

	sprintf(buf, "\033[%d;%dR", vc->vc_y + (vc->vc_decom ? vc->vc_top + 1 : 1), vc->vc_x + 1);
	respond_string(buf, tty);
}
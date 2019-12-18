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
 int /*<<< orphan*/  OSSetExceptionCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_EXCEPTION_TYPE_DSI ; 
 int /*<<< orphan*/  OS_EXCEPTION_TYPE_ISI ; 
 int /*<<< orphan*/  OS_EXCEPTION_TYPE_PROGRAM ; 
 int /*<<< orphan*/  exception_dsi_cb ; 
 int /*<<< orphan*/  exception_isi_cb ; 
 int /*<<< orphan*/  exception_msgbuf ; 
 int /*<<< orphan*/  exception_prog_cb ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  test_os_exceptions () ; 

void setup_os_exceptions(void)
{
   exception_msgbuf = malloc(4096);
   OSSetExceptionCallback(OS_EXCEPTION_TYPE_DSI, exception_dsi_cb);
   OSSetExceptionCallback(OS_EXCEPTION_TYPE_ISI, exception_isi_cb);
   OSSetExceptionCallback(OS_EXCEPTION_TYPE_PROGRAM, exception_prog_cb);
   test_os_exceptions();
}
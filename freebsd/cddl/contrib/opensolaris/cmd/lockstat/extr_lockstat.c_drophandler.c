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
struct TYPE_3__ {char* dtdda_msg; } ;
typedef  TYPE_1__ dtrace_dropdata_t ;

/* Variables and functions */
 int DTRACE_HANDLE_OK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  g_dropped ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
drophandler(const dtrace_dropdata_t *data, void *arg)
{
	g_dropped++;
	(void) fprintf(stderr, "lockstat: warning: %s", data->dtdda_msg);
	return (DTRACE_HANDLE_OK);
}
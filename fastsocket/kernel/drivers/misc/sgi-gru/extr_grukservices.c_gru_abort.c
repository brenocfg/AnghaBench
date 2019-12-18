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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int GRU_EXC_STR_SIZE ; 
 int /*<<< orphan*/  gru_get_cb_exception_detail_str (int,void*,char*,int) ; 
 int /*<<< orphan*/  panic (char*,char*,int /*<<< orphan*/ ) ; 

void gru_abort(int ret, void *cb, char *str)
{
	char buf[GRU_EXC_STR_SIZE];

	panic("GRU FATAL ERROR: %s - %s\n", str,
	      gru_get_cb_exception_detail_str(ret, cb, buf, sizeof(buf)));
}
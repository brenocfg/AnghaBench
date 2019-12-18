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
struct wlp_options {int /*<<< orphan*/  def_tx_hdr; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int wlp_tx_hdr_rts_cts (int /*<<< orphan*/ *) ; 

ssize_t uwb_rts_cts_show(const struct wlp_options *options, char *buf)
{
	return sprintf(buf, "%u\n",
		       wlp_tx_hdr_rts_cts(&options->def_tx_hdr));
}
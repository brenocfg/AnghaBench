#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/  controller_xmit_window; int /*<<< orphan*/  num_lm_acl_bufs; } ;

/* Variables and functions */
 TYPE_1__ l2cb ; 

void l2c_link_processs_num_bufs (UINT16 num_lm_acl_bufs)
{
    l2cb.num_lm_acl_bufs = l2cb.controller_xmit_window = num_lm_acl_bufs;

}
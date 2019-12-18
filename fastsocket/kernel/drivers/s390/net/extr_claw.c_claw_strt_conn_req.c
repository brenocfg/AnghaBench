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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int claw_snd_conn_req (struct net_device*,int) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static int
claw_strt_conn_req(struct net_device *dev )
{
        int rc;

	CLAW_DBF_TEXT(2, setup, "conn_req");
        rc=claw_snd_conn_req(dev, 1);
        return rc;
}
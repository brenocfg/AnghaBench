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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  port_id; } ;
struct fc_rport_priv {TYPE_1__ ids; } ;
struct fc_els_spp {int /*<<< orphan*/  spp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ft_lport_lock ; 
 int ft_prli_locked (struct fc_rport_priv*,int /*<<< orphan*/ ,struct fc_els_spp const*,struct fc_els_spp*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ft_prli(struct fc_rport_priv *rdata, u32 spp_len,
		   const struct fc_els_spp *rspp, struct fc_els_spp *spp)
{
	int ret;

	mutex_lock(&ft_lport_lock);
	ret = ft_prli_locked(rdata, spp_len, rspp, spp);
	mutex_unlock(&ft_lport_lock);
	pr_debug("port_id %x flags %x ret %x\n",
	       rdata->ids.port_id, rspp ? rspp->spp_flags : 0, ret);
	return ret;
}
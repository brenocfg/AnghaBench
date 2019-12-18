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
struct soc_pcmcia_socket {int /*<<< orphan*/  res_skt; int /*<<< orphan*/  res_io; int /*<<< orphan*/  res_mem; int /*<<< orphan*/  res_attr; int /*<<< orphan*/ * virt_io; int /*<<< orphan*/  node; TYPE_1__* ops; int /*<<< orphan*/  socket; int /*<<< orphan*/  poll_timer; } ;
struct skt_dev_info {int nskt; struct soc_pcmcia_socket* skt; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hw_shutdown ) (struct soc_pcmcia_socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct skt_dev_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct skt_dev_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_common_pcmcia_config_skt (struct soc_pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_pcmcia_cpufreq_unregister () ; 
 int /*<<< orphan*/  soc_pcmcia_sockets ; 
 int /*<<< orphan*/  soc_pcmcia_sockets_lock ; 
 int /*<<< orphan*/  stub1 (struct soc_pcmcia_socket*) ; 

int soc_common_drv_pcmcia_remove(struct device *dev)
{
	struct skt_dev_info *sinfo = dev_get_drvdata(dev);
	int i;

	dev_set_drvdata(dev, NULL);

	mutex_lock(&soc_pcmcia_sockets_lock);
	for (i = 0; i < sinfo->nskt; i++) {
		struct soc_pcmcia_socket *skt = &sinfo->skt[i];

		del_timer_sync(&skt->poll_timer);

		pcmcia_unregister_socket(&skt->socket);

		flush_scheduled_work();

		skt->ops->hw_shutdown(skt);

		soc_common_pcmcia_config_skt(skt, &dead_socket);

		list_del(&skt->node);
		iounmap(skt->virt_io);
		skt->virt_io = NULL;
		release_resource(&skt->res_attr);
		release_resource(&skt->res_mem);
		release_resource(&skt->res_io);
		release_resource(&skt->res_skt);
	}
	if (list_empty(&soc_pcmcia_sockets))
		soc_pcmcia_cpufreq_unregister();

	mutex_unlock(&soc_pcmcia_sockets_lock);

	kfree(sinfo);

	return 0;
}
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
typedef  int u32 ;
struct skt_dev_info {int nskt; } ;
struct platform_device {int dummy; } ;
struct au1000_pcmcia_socket {int /*<<< orphan*/ * virt_io; TYPE_1__* ops; int /*<<< orphan*/  socket; int /*<<< orphan*/  poll_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hw_shutdown ) (struct au1000_pcmcia_socket*) ;} ;

/* Variables and functions */
 struct au1000_pcmcia_socket* PCMCIA_SOCKET (int) ; 
 int /*<<< orphan*/  au1x00_pcmcia_config_skt (struct au1000_pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct skt_dev_info*) ; 
 scalar_t__ mips_io_port_base ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_sockets_lock ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (int /*<<< orphan*/ *) ; 
 struct skt_dev_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct au1000_pcmcia_socket*) ; 

int au1x00_drv_pcmcia_remove(struct platform_device *dev)
{
	struct skt_dev_info *sinfo = platform_get_drvdata(dev);
	int i;

	mutex_lock(&pcmcia_sockets_lock);
	platform_set_drvdata(dev, NULL);

	for (i = 0; i < sinfo->nskt; i++) {
		struct au1000_pcmcia_socket *skt = PCMCIA_SOCKET(i);

		del_timer_sync(&skt->poll_timer);
		pcmcia_unregister_socket(&skt->socket);
		flush_scheduled_work();
		skt->ops->hw_shutdown(skt);
		au1x00_pcmcia_config_skt(skt, &dead_socket);
		iounmap(skt->virt_io + (u32)mips_io_port_base);
		skt->virt_io = NULL;
	}

	kfree(sinfo);
	mutex_unlock(&pcmcia_sockets_lock);
	return 0;
}
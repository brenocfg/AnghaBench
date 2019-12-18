#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct nouveau_drm {TYPE_2__ client; int /*<<< orphan*/  clients; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  vm; } ;
struct nouveau_cli {int /*<<< orphan*/  head; TYPE_1__ base; } ;
struct drm_file {int pid; struct nouveau_cli* driver_priv; } ;
struct drm_device {struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_7__ {scalar_t__ card_type; } ;

/* Variables and functions */
 scalar_t__ NV_50 ; 
 int TASK_COMM_LEN ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_task_comm (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nouveau_cli_create (struct pci_dev*,char*,int,void**) ; 
 int /*<<< orphan*/  nouveau_cli_destroy (struct nouveau_cli*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int nouveau_vm_new (TYPE_3__*,int /*<<< orphan*/ ,unsigned long long,int,int /*<<< orphan*/ *) ; 
 TYPE_3__* nv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static int
nouveau_drm_open(struct drm_device *dev, struct drm_file *fpriv)
{
	struct pci_dev *pdev = dev->pdev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_cli *cli;
	char name[32], tmpname[TASK_COMM_LEN];
	int ret;

	get_task_comm(tmpname, current);
	snprintf(name, sizeof(name), "%s[%d]", tmpname, fpriv->pid);

	ret = nouveau_cli_create(pdev, name, sizeof(*cli), (void **)&cli);
	if (ret)
		return ret;

	if (nv_device(drm->device)->card_type >= NV_50) {
		ret = nouveau_vm_new(nv_device(drm->device), 0, (1ULL << 40),
				     0x1000, &cli->base.vm);
		if (ret) {
			nouveau_cli_destroy(cli);
			return ret;
		}
	}

	fpriv->driver_priv = cli;

	mutex_lock(&drm->client.mutex);
	list_add(&cli->head, &drm->clients);
	mutex_unlock(&drm->client.mutex);
	return 0;
}
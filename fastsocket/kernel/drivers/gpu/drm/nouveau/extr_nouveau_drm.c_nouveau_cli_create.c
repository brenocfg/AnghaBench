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
struct pci_dev {int dummy; } ;
struct nouveau_cli {int /*<<< orphan*/  mutex; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nouveau_client_create_ (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  nouveau_client_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_config ; 
 int /*<<< orphan*/  nouveau_debug ; 
 int /*<<< orphan*/  nouveau_name (struct pci_dev*) ; 

__attribute__((used)) static int
nouveau_cli_create(struct pci_dev *pdev, const char *name,
		   int size, void **pcli)
{
	struct nouveau_cli *cli;
	int ret;

	*pcli = NULL;
	ret = nouveau_client_create_(name, nouveau_name(pdev), nouveau_config,
				     nouveau_debug, size, pcli);
	cli = *pcli;
	if (ret) {
		if (cli)
			nouveau_client_destroy(&cli->base);
		*pcli = NULL;
		return ret;
	}

	mutex_init(&cli->mutex);
	return 0;
}
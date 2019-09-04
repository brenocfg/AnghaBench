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
struct TYPE_2__ {int /*<<< orphan*/  image; } ;
struct dso {struct dso* next; TYPE_1__ tls; int /*<<< orphan*/  tls_id; int /*<<< orphan*/  phnum; int /*<<< orphan*/  phdr; int /*<<< orphan*/  name; scalar_t__ base; } ;
struct dl_phdr_info {uintptr_t dlpi_addr; int /*<<< orphan*/  dlpi_tls_data; int /*<<< orphan*/  dlpi_tls_modid; scalar_t__ dlpi_subs; int /*<<< orphan*/  dlpi_adds; int /*<<< orphan*/  dlpi_phnum; int /*<<< orphan*/  dlpi_phdr; int /*<<< orphan*/  dlpi_name; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int callback ;

/* Variables and functions */
 int /*<<< orphan*/  gencnt ; 
 struct dso* head ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 

int dl_iterate_phdr(int(*callback)(struct dl_phdr_info *info, size_t size, void *data), void *data)
{
	struct dso *current;
	struct dl_phdr_info info;
	int ret = 0;
	for(current = head; current;) {
		info.dlpi_addr      = (uintptr_t)current->base;
		info.dlpi_name      = current->name;
		info.dlpi_phdr      = current->phdr;
		info.dlpi_phnum     = current->phnum;
		info.dlpi_adds      = gencnt;
		info.dlpi_subs      = 0;
		info.dlpi_tls_modid = current->tls_id;
		info.dlpi_tls_data  = current->tls.image;

		ret = (callback)(&info, sizeof (info), data);

		if (ret != 0) break;

		pthread_rwlock_rdlock(&lock);
		current = current->next;
		pthread_rwlock_unlock(&lock);
	}
	return ret;
}
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
struct cyclades_port {scalar_t__ magic; } ;

/* Variables and functions */
 scalar_t__ CYCLADES_MAGIC ; 
 size_t NR_PORTS ; 
 struct cyclades_port* cy_port ; 
 int /*<<< orphan*/  printk (char*,char*,char const*) ; 

__attribute__((used)) static inline int serial_paranoia_check(struct cyclades_port *info, char *name,
		const char *routine)
{
#ifdef SERIAL_PARANOIA_CHECK
	if (!info) {
		printk("Warning: null cyclades_port for (%s) in %s\n", name,
				routine);
		return 1;
	}

	if (info < &cy_port[0] || info >= &cy_port[NR_PORTS]) {
		printk("Warning: cyclades_port out of range for (%s) in %s\n",
				name, routine);
		return 1;
	}

	if (info->magic != CYCLADES_MAGIC) {
		printk("Warning: bad magic number for serial struct (%s) in "
				"%s\n", name, routine);
		return 1;
	}
#endif
	return 0;
}
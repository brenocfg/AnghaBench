#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * gate_addr; } ;
struct TYPE_5__ {int fixed_config; int fd; int /*<<< orphan*/  dev_name; } ;
struct TYPE_6__ {TYPE_1__ tuntap; } ;
struct TYPE_7__ {int /*<<< orphan*/  poll; int /*<<< orphan*/  protocol; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ info; } ;
struct iss_net_private {int have_mac; TYPE_4__ host; TYPE_3__ tp; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRANSPORT_TUNTAP_MTU ; 
 int /*<<< orphan*/  TRANSPORT_TUNTAP_NAME ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ setup_etheraddr (char*,int /*<<< orphan*/ ) ; 
 char* split_if_spec (char*,char**,char**) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tuntap_close ; 
 int /*<<< orphan*/  tuntap_open ; 
 int /*<<< orphan*/  tuntap_poll ; 
 int /*<<< orphan*/  tuntap_protocol ; 
 int /*<<< orphan*/  tuntap_read ; 
 int /*<<< orphan*/  tuntap_write ; 

__attribute__((used)) static int tuntap_probe(struct iss_net_private *lp, int index, char *init)
{
	const int len = strlen(TRANSPORT_TUNTAP_NAME);
	char *dev_name = NULL, *mac_str = NULL, *rem = NULL;

	/* Transport should be 'tuntap': ethX=tuntap,mac,dev_name */

	if (strncmp(init, TRANSPORT_TUNTAP_NAME, len))
		return 0;

	if (*(init += strlen(TRANSPORT_TUNTAP_NAME)) == ',') {
		if ((rem=split_if_spec(init+1, &mac_str, &dev_name)) != NULL) {
			printk("Extra garbage on specification : '%s'\n", rem);
			return 0;
		}
	} else if (*init != '\0') {
		printk("Invalid argument: %s. Skipping device!\n", init);
		return 0;
	}

	if (dev_name) {
		strncpy(lp->tp.info.tuntap.dev_name, dev_name,
			 sizeof lp->tp.info.tuntap.dev_name);
		lp->tp.info.tuntap.fixed_config = 1;
	} else
		strcpy(lp->tp.info.tuntap.dev_name, TRANSPORT_TUNTAP_NAME);


#if 0
	if (setup_etheraddr(mac_str, lp->mac))
		lp->have_mac = 1;
#endif
	lp->mtu = TRANSPORT_TUNTAP_MTU;

	//lp->info.tuntap.gate_addr = gate_addr;

	lp->tp.info.tuntap.fd = -1;

	lp->tp.open = tuntap_open;
	lp->tp.close = tuntap_close;
	lp->tp.read = tuntap_read;
	lp->tp.write = tuntap_write;
	lp->tp.protocol = tuntap_protocol;
	lp->tp.poll = tuntap_poll;

	printk("TUN/TAP backend - ");
#if 0
	if (lp->host.gate_addr != NULL)
		printk("IP = %s", lp->host.gate_addr);
#endif
	printk("\n");

	return 1;
}
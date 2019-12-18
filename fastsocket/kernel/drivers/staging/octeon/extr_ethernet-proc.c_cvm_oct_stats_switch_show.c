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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mdio_write ) (struct net_device*,int,int,int) ;} ;
struct octeon_ethernet {TYPE_1__ mii_info; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_device** cvm_oct_device ; 
 int cvm_oct_stats_read_switch (struct net_device*,int,int) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int const,...) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int,int) ; 

__attribute__((used)) static int cvm_oct_stats_switch_show(struct seq_file *m, void *v)
{
	static const int ports[] = { 0, 1, 2, 3, 9, -1 };
	struct net_device *dev = cvm_oct_device[0];
	int index = 0;

	while (ports[index] != -1) {

		/* Latch port */
		struct octeon_ethernet *priv = netdev_priv(dev);

		priv->mii_info.mdio_write(dev, 0x1b, 0x1d,
					  0xdc00 | ports[index]);
		seq_printf(m, "\nSwitch Port %d\n", ports[index]);
		seq_printf(m, "InGoodOctets:   %12llu\t"
			   "OutOctets:      %12llu\t"
			   "64 Octets:      %12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b,
						     0x00) |
			   (cvm_oct_stats_read_switch(dev, 0x1b, 0x01) << 32),
			   cvm_oct_stats_read_switch(dev, 0x1b,
						     0x0E) |
			   (cvm_oct_stats_read_switch(dev, 0x1b, 0x0F) << 32),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x08));

		seq_printf(m, "InBadOctets:    %12llu\t"
			   "OutUnicast:     %12llu\t"
			   "65-127 Octets:  %12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x02),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x10),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x09));

		seq_printf(m, "InUnicast:      %12llu\t"
			   "OutBroadcasts:  %12llu\t"
			   "128-255 Octets: %12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x04),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x13),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x0A));

		seq_printf(m, "InBroadcasts:   %12llu\t"
			   "OutMulticasts:  %12llu\t"
			   "256-511 Octets: %12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x06),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x12),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x0B));

		seq_printf(m, "InMulticasts:   %12llu\t"
			   "OutPause:       %12llu\t"
			   "512-1023 Octets:%12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x07),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x15),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x0C));

		seq_printf(m, "InPause:        %12llu\t"
			   "Excessive:      %12llu\t"
			   "1024-Max Octets:%12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x16),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x11),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x0D));

		seq_printf(m, "InUndersize:    %12llu\t"
			   "Collisions:     %12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x18),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x1E));

		seq_printf(m, "InFragments:    %12llu\t"
			   "Deferred:       %12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x19),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x05));

		seq_printf(m, "InOversize:     %12llu\t"
			   "Single:         %12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x1A),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x14));

		seq_printf(m, "InJabber:       %12llu\t"
			   "Multiple:       %12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x1B),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x17));

		seq_printf(m, "In RxErr:       %12llu\t"
			   "OutFCSErr:      %12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x1C),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x03));

		seq_printf(m, "InFCSErr:       %12llu\t"
			   "Late:           %12llu\n",
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x1D),
			   cvm_oct_stats_read_switch(dev, 0x1b, 0x1F));
		index++;
	}
	return 0;
}
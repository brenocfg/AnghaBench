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
struct sil24_port_priv {scalar_t__ do_port_rst; } ;
struct ata_port {struct sil24_port_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_eh_freeze_port (struct ata_port*) ; 
 int /*<<< orphan*/  sata_pmp_error_handler (struct ata_port*) ; 
 scalar_t__ sil24_init_port (struct ata_port*) ; 

__attribute__((used)) static void sil24_error_handler(struct ata_port *ap)
{
	struct sil24_port_priv *pp = ap->private_data;

	if (sil24_init_port(ap))
		ata_eh_freeze_port(ap);

	sata_pmp_error_handler(ap);

	pp->do_port_rst = 0;
}
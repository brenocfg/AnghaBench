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
struct seq_file {scalar_t__ private; } ;
struct TYPE_2__ {int chipset; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
#define  ide_4drives 140 
#define  ide_acorn 139 
#define  ide_ali14xx 138 
#define  ide_au1xxx 137 
#define  ide_cmd640 136 
#define  ide_dtc2278 135 
#define  ide_generic 134 
#define  ide_ht6560b 133 
#define  ide_palm3710 132 
#define  ide_pci 131 
#define  ide_pmac 130 
#define  ide_qd65xx 129 
#define  ide_umc8672 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*) ; 

__attribute__((used)) static int ide_imodel_proc_show(struct seq_file *m, void *v)
{
	ide_hwif_t	*hwif = (ide_hwif_t *) m->private;
	const char	*name;

	switch (hwif->chipset) {
	case ide_generic:	name = "generic";	break;
	case ide_pci:		name = "pci";		break;
	case ide_cmd640:	name = "cmd640";	break;
	case ide_dtc2278:	name = "dtc2278";	break;
	case ide_ali14xx:	name = "ali14xx";	break;
	case ide_qd65xx:	name = "qd65xx";	break;
	case ide_umc8672:	name = "umc8672";	break;
	case ide_ht6560b:	name = "ht6560b";	break;
	case ide_4drives:	name = "4drives";	break;
	case ide_pmac:		name = "mac-io";	break;
	case ide_au1xxx:	name = "au1xxx";	break;
	case ide_palm3710:      name = "palm3710";      break;
	case ide_acorn:		name = "acorn";		break;
	default:		name = "(unknown)";	break;
	}
	seq_printf(m, "%s\n", name);
	return 0;
}
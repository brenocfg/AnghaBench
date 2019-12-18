#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
typedef  void* UINT ;
typedef  int U8 ;
typedef  int U16 ;
struct TYPE_3__ {int byRevId; struct pci_dev* pcid; void* ioaddr; void* memaddr; int /*<<< orphan*/  SubVendorID; int /*<<< orphan*/  SubSystemID; } ;
typedef  TYPE_1__* PSDevice ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int PCI_COMMAND ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_REVISION_ID ; 
 int PCI_SUBSYSTEM_ID ; 
 int PCI_SUBSYSTEM_VENDOR_ID ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static BOOL device_get_pci_info(PSDevice pDevice, struct pci_dev* pcid) {

    U16 pci_cmd;
    U8  b;
    UINT cis_addr;
#ifdef	PLICE_DEBUG
	BYTE       pci_config[256];
	BYTE	value =0x00;
	int		ii,j;
	U16	max_lat=0x0000;
	memset(pci_config,0x00,256);
#endif

    pci_read_config_byte(pcid, PCI_REVISION_ID, &pDevice->byRevId);
    pci_read_config_word(pcid, PCI_SUBSYSTEM_ID,&pDevice->SubSystemID);
    pci_read_config_word(pcid, PCI_SUBSYSTEM_VENDOR_ID, &pDevice->SubVendorID);
    pci_read_config_word(pcid, PCI_COMMAND, (u16 *) & (pci_cmd));

    pci_set_master(pcid);

    pDevice->memaddr = pci_resource_start(pcid,0);
    pDevice->ioaddr = pci_resource_start(pcid,1);

#ifdef	DEBUG
//	pDevice->ioaddr = pci_resource_start(pcid, 0);
//	pDevice->memaddr = pci_resource_start(pcid,1);
#endif

    cis_addr = pci_resource_start(pcid,2);

    pDevice->pcid = pcid;

    pci_read_config_byte(pcid, PCI_COMMAND, &b);
    pci_write_config_byte(pcid, PCI_COMMAND, (b|PCI_COMMAND_MASTER));

#ifdef	PLICE_DEBUG
   	//pci_read_config_word(pcid,PCI_MAX_LAT,&max_lat);
	//printk("max lat is %x,SubSystemID is %x\n",max_lat,pDevice->SubSystemID);
	//for (ii=0;ii<0xFF;ii++)
	//pci_read_config_word(pcid,PCI_MAX_LAT,&max_lat);
	//max_lat  = 0x20;
	//pci_write_config_word(pcid,PCI_MAX_LAT,max_lat);
	//pci_read_config_word(pcid,PCI_MAX_LAT,&max_lat);
	//printk("max lat is %x\n",max_lat);

	for (ii=0;ii<0xFF;ii++)
	{
		pci_read_config_byte(pcid,ii,&value);
		pci_config[ii] = value;
	}
	for (ii=0,j=1;ii<0x100;ii++,j++)
	{
		if (j %16 == 0)
		{
			printk("%x:",pci_config[ii]);
			printk("\n");
		}
		else
		{
			printk("%x:",pci_config[ii]);
		}
	}
#endif
    return TRUE;
}
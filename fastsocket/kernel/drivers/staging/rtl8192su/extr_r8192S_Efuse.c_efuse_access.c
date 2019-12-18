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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EFUSE_CLK_CTRL ; 
 int EFUSE_TEST ; 
 int SYS_FUNC_EN ; 
 int /*<<< orphan*/  efuse_OneByteRead (struct net_device*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  efuse_one_byte_rw (struct net_device*,int,int,int*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int read_nic_byte (struct net_device*,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int,int) ; 

void efuse_access(struct net_device* dev, u8 bRead,u16 start_addr, u8 cnts, u8 *data)
{
	u8	efuse_clk_ori,efuse_clk_new;//,tmp8;
	u32 i = 0;

	if(start_addr>0x200) return;
	//RT_TRACE(_module_rtl871x_mp_ioctl_c_,_drv_err_,
	//	("\n ===> efuse_access [start_addr=0x%x cnts:%d dataarray:0x%08x  Query Efuse].\n",start_addr,cnts,data));
	// -----------------SYS_FUNC_EN Digital Core Vdd enable ---------------------------------
	efuse_clk_ori = read_nic_byte(dev,SYS_FUNC_EN+1);
	efuse_clk_new = efuse_clk_ori|0x20;

	if(efuse_clk_new!= efuse_clk_ori){
		//RT_TRACE(_module_rtl871x_mp_ioctl_c_,_drv_err_,("====write 0x10250003=====\n"));
		write_nic_byte(dev, SYS_FUNC_EN+1, efuse_clk_new);
	}
#ifdef _POWERON_DELAY_
	mdelay(10);
#endif
	// -----------------e-fuse pwr & clk reg ctrl ---------------------------------
	write_nic_byte(dev, EFUSE_TEST+3, (read_nic_byte(dev, EFUSE_TEST+3)|0x80));
	write_nic_byte(dev, EFUSE_CLK_CTRL, (read_nic_byte(dev, EFUSE_CLK_CTRL)|0x03));

#ifdef _PRE_EXECUTE_READ_CMD_
	{
		unsigned char tmpdata;
		efuse_OneByteRead(dev, 0,&tmpdata);
	}
#endif

	//-----------------e-fuse one byte read / write ------------------------------
	for(i=0;i<cnts;i++){
		efuse_one_byte_rw(dev,bRead, start_addr+i , data+i);
		////RT_TRACE(_module_rtl871x_mp_ioctl_c_,_drv_err_,("==>efuse_access addr:0x%02x value:0x%02x\n",data+i,*(data+i)));
	}
	// -----------------e-fuse pwr & clk reg ctrl ---------------------------------
	write_nic_byte(dev, EFUSE_TEST+3, read_nic_byte(dev, EFUSE_TEST+3)&0x7f);
	write_nic_byte(dev, EFUSE_CLK_CTRL, read_nic_byte(dev, EFUSE_CLK_CTRL)&0xfd);

	// -----------------SYS_FUNC_EN Digital Core Vdd disable ---------------------------------
	if(efuse_clk_new != efuse_clk_ori)	write_nic_byte(dev, 0x10250003, efuse_clk_ori);

}
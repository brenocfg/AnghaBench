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
typedef  int u32 ;
struct nouveau_pm_memtiming {int* mr; } ;
struct nouveau_pm_level {struct nouveau_pm_memtiming timing; } ;
struct nouveau_mem_exec_func {int (* mrg ) (struct nouveau_mem_exec_func*,int) ;int /*<<< orphan*/  (* precharge ) (struct nouveau_mem_exec_func*) ;int /*<<< orphan*/  (* wait ) (struct nouveau_mem_exec_func*,int) ;int /*<<< orphan*/  (* mrs ) (struct nouveau_mem_exec_func*,int,int) ;int /*<<< orphan*/  (* timing_set ) (struct nouveau_mem_exec_func*) ;int /*<<< orphan*/  (* refresh_auto ) (struct nouveau_mem_exec_func*,int) ;int /*<<< orphan*/  (* refresh_self ) (struct nouveau_mem_exec_func*,int) ;int /*<<< orphan*/  (* clock_set ) (struct nouveau_mem_exec_func*) ;int /*<<< orphan*/  (* refresh ) (struct nouveau_mem_exec_func*) ;int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int type; } ;
struct nouveau_fb {TYPE_1__ ram; } ;
struct nouveau_drm {int dummy; } ;
struct nouveau_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
#define  NV_MEM_TYPE_DDR2 130 
#define  NV_MEM_TYPE_DDR3 129 
#define  NV_MEM_TYPE_GDDR3 128 
 struct nouveau_device* nouveau_dev (int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 struct nouveau_fb* nouveau_fb (struct nouveau_device*) ; 
 int stub1 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub10 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub11 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub12 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub13 (struct nouveau_mem_exec_func*) ; 
 int /*<<< orphan*/  stub14 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub15 (struct nouveau_mem_exec_func*) ; 
 int /*<<< orphan*/  stub16 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub17 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub18 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub19 (struct nouveau_mem_exec_func*,int) ; 
 int stub2 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub20 (struct nouveau_mem_exec_func*,int,int) ; 
 int /*<<< orphan*/  stub21 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub22 (struct nouveau_mem_exec_func*,int,int) ; 
 int /*<<< orphan*/  stub23 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub24 (struct nouveau_mem_exec_func*,int,int) ; 
 int /*<<< orphan*/  stub25 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub26 (struct nouveau_mem_exec_func*) ; 
 int /*<<< orphan*/  stub27 (struct nouveau_mem_exec_func*,int,int) ; 
 int /*<<< orphan*/  stub28 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub29 (struct nouveau_mem_exec_func*,int,int) ; 
 int stub3 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub30 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub31 (struct nouveau_mem_exec_func*,int,int) ; 
 int /*<<< orphan*/  stub32 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub33 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub34 (struct nouveau_mem_exec_func*) ; 
 int /*<<< orphan*/  stub4 (struct nouveau_mem_exec_func*) ; 
 int /*<<< orphan*/  stub5 (struct nouveau_mem_exec_func*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct nouveau_mem_exec_func*,int) ; 
 int /*<<< orphan*/  stub7 (struct nouveau_mem_exec_func*) ; 
 int /*<<< orphan*/  stub8 (struct nouveau_mem_exec_func*) ; 
 int /*<<< orphan*/  stub9 (struct nouveau_mem_exec_func*) ; 

int
nouveau_mem_exec(struct nouveau_mem_exec_func *exec,
		 struct nouveau_pm_level *perflvl)
{
	struct nouveau_drm *drm = nouveau_drm(exec->dev);
	struct nouveau_device *device = nouveau_dev(exec->dev);
	struct nouveau_fb *pfb = nouveau_fb(device);
	struct nouveau_pm_memtiming *info = &perflvl->timing;
	u32 tMRD = 1000, tCKSRE = 0, tCKSRX = 0, tXS = 0, tDLLK = 0;
	u32 mr[3] = { info->mr[0], info->mr[1], info->mr[2] };
	u32 mr1_dlloff;

	switch (pfb->ram.type) {
	case NV_MEM_TYPE_DDR2:
		tDLLK = 2000;
		mr1_dlloff = 0x00000001;
		break;
	case NV_MEM_TYPE_DDR3:
		tDLLK = 12000;
		tCKSRE = 2000;
		tXS = 1000;
		mr1_dlloff = 0x00000001;
		break;
	case NV_MEM_TYPE_GDDR3:
		tDLLK = 40000;
		mr1_dlloff = 0x00000040;
		break;
	default:
		NV_ERROR(drm, "cannot reclock unsupported memtype\n");
		return -ENODEV;
	}

	/* fetch current MRs */
	switch (pfb->ram.type) {
	case NV_MEM_TYPE_GDDR3:
	case NV_MEM_TYPE_DDR3:
		mr[2] = exec->mrg(exec, 2);
	default:
		mr[1] = exec->mrg(exec, 1);
		mr[0] = exec->mrg(exec, 0);
		break;
	}

	/* DLL 'on' -> DLL 'off' mode, disable before entering self-refresh  */
	if (!(mr[1] & mr1_dlloff) && (info->mr[1] & mr1_dlloff)) {
		exec->precharge(exec);
		exec->mrs (exec, 1, mr[1] | mr1_dlloff);
		exec->wait(exec, tMRD);
	}

	/* enter self-refresh mode */
	exec->precharge(exec);
	exec->refresh(exec);
	exec->refresh(exec);
	exec->refresh_auto(exec, false);
	exec->refresh_self(exec, true);
	exec->wait(exec, tCKSRE);

	/* modify input clock frequency */
	exec->clock_set(exec);

	/* exit self-refresh mode */
	exec->wait(exec, tCKSRX);
	exec->precharge(exec);
	exec->refresh_self(exec, false);
	exec->refresh_auto(exec, true);
	exec->wait(exec, tXS);
	exec->wait(exec, tXS);

	/* update MRs */
	if (mr[2] != info->mr[2]) {
		exec->mrs (exec, 2, info->mr[2]);
		exec->wait(exec, tMRD);
	}

	if (mr[1] != info->mr[1]) {
		/* need to keep DLL off until later, at least on GDDR3 */
		exec->mrs (exec, 1, info->mr[1] | (mr[1] & mr1_dlloff));
		exec->wait(exec, tMRD);
	}

	if (mr[0] != info->mr[0]) {
		exec->mrs (exec, 0, info->mr[0]);
		exec->wait(exec, tMRD);
	}

	/* update PFB timing registers */
	exec->timing_set(exec);

	/* DLL (enable + ) reset */
	if (!(info->mr[1] & mr1_dlloff)) {
		if (mr[1] & mr1_dlloff) {
			exec->mrs (exec, 1, info->mr[1]);
			exec->wait(exec, tMRD);
		}
		exec->mrs (exec, 0, info->mr[0] | 0x00000100);
		exec->wait(exec, tMRD);
		exec->mrs (exec, 0, info->mr[0] | 0x00000000);
		exec->wait(exec, tMRD);
		exec->wait(exec, tDLLK);
		if (pfb->ram.type == NV_MEM_TYPE_GDDR3)
			exec->precharge(exec);
	}

	return 0;
}
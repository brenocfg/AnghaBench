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
typedef  int UWORD ;

/* Variables and functions */
 int Atari800_os_version ; 
 int /*<<< orphan*/  BINLOAD_loading_basic ; 
 int /*<<< orphan*/  Devices_E_Read ; 
 int /*<<< orphan*/  Devices_E_Write ; 
 int /*<<< orphan*/  Devices_IgnoreReady ; 
 int /*<<< orphan*/  Devices_K_Read ; 
 int /*<<< orphan*/  Devices_P_Close ; 
 int /*<<< orphan*/  Devices_P_Init ; 
 int /*<<< orphan*/  Devices_P_Open ; 
 int /*<<< orphan*/  Devices_P_Status ; 
 int /*<<< orphan*/  Devices_P_Write ; 
 int Devices_TABLE_CLOS ; 
 int Devices_TABLE_INIT ; 
 int Devices_TABLE_OPEN ; 
 int Devices_TABLE_READ ; 
 int Devices_TABLE_STAT ; 
 int Devices_TABLE_WRIT ; 
 int /*<<< orphan*/  Devices_enable_p_patch ; 
 int /*<<< orphan*/  ESC_AddEscRts (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESC_AddEscRts2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESC_EHREAD ; 
 int /*<<< orphan*/  ESC_EHWRIT ; 
 int /*<<< orphan*/  ESC_KHREAD ; 
 int /*<<< orphan*/  ESC_PHCLOS ; 
 int /*<<< orphan*/  ESC_PHINIT ; 
 int /*<<< orphan*/  ESC_PHOPEN ; 
 int /*<<< orphan*/  ESC_PHSTAT ; 
 int /*<<< orphan*/  ESC_PHWRIT ; 
 int /*<<< orphan*/  ESC_Remove (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int MEMORY_dGetByte (int) ; 
 int MEMORY_dGetWord (int) ; 
#define  SYSROM_800_CUSTOM 143 
#define  SYSROM_AA00R10 142 
#define  SYSROM_AA01R11 141 
#define  SYSROM_A_NTSC 140 
#define  SYSROM_A_PAL 139 
#define  SYSROM_BB00R1 138 
#define  SYSROM_BB01R2 137 
#define  SYSROM_BB01R3 136 
#define  SYSROM_BB01R4_OS 135 
#define  SYSROM_BB01R59 134 
#define  SYSROM_BB01R59A 133 
#define  SYSROM_BB02R3 132 
#define  SYSROM_BB02R3V4 131 
#define  SYSROM_B_NTSC 130 
#define  SYSROM_CC01R4 129 
#define  SYSROM_XL_CUSTOM 128 
 int TRUE ; 
 int /*<<< orphan*/  ehclos_addr ; 
 int /*<<< orphan*/  ehopen_addr ; 
 int /*<<< orphan*/  ehread_addr ; 
 int ehwrit_addr ; 
 int /*<<< orphan*/  ready_prompt ; 
 int /*<<< orphan*/  ready_ptr ; 

int Devices_PatchOS(void)
{
	UWORD addr;
	int i;
	int patched = FALSE;

	switch (Atari800_os_version) {
	case SYSROM_A_NTSC:
	case SYSROM_A_PAL:
	case SYSROM_B_NTSC:
	case SYSROM_800_CUSTOM:
		addr = 0xf0e3;
		break;
	case SYSROM_AA00R10:
		addr = 0xc4fa;
		break;
	case SYSROM_AA01R11:
		addr = 0xc479;
		break;
	case SYSROM_BB00R1:
		addr = 0xc43c;
		break;
	case SYSROM_BB01R2:
	case SYSROM_BB01R3:
	case SYSROM_BB01R4_OS:
	case SYSROM_BB01R59:
	case SYSROM_BB01R59A:
	case SYSROM_XL_CUSTOM:
		addr = 0xc42e;
		break;
	case SYSROM_BB02R3:
		addr = 0xc42c;
		break;
	case SYSROM_BB02R3V4:
		addr = 0xc43b;
		break;
	case SYSROM_CC01R4:
		addr = 0xc3eb;
		break;
	default:
		return FALSE;
	}

	for (i = 0; i < 5; i++) {
		UWORD devtab = MEMORY_dGetWord(addr + 1);
		switch (MEMORY_dGetByte(addr)) {
#ifdef HAVE_SYSTEM
		case 'P':
			if (Devices_enable_p_patch) {
				ESC_AddEscRts((UWORD) (MEMORY_dGetWord(devtab + Devices_TABLE_OPEN) + 1),
				                   ESC_PHOPEN, Devices_P_Open);
				ESC_AddEscRts((UWORD) (MEMORY_dGetWord(devtab + Devices_TABLE_CLOS) + 1),
				                   ESC_PHCLOS, Devices_P_Close);
				ESC_AddEscRts((UWORD) (MEMORY_dGetWord(devtab + Devices_TABLE_WRIT) + 1),
				                   ESC_PHWRIT, Devices_P_Write);
				ESC_AddEscRts((UWORD) (MEMORY_dGetWord(devtab + Devices_TABLE_STAT) + 1),
				                   ESC_PHSTAT, Devices_P_Status);
				ESC_AddEscRts2((UWORD) (devtab + Devices_TABLE_INIT), ESC_PHINIT,
				                    Devices_P_Init);
				patched = TRUE;
			}
			else {
				ESC_Remove(ESC_PHOPEN);
				ESC_Remove(ESC_PHCLOS);
				ESC_Remove(ESC_PHWRIT);
				ESC_Remove(ESC_PHSTAT);
				ESC_Remove(ESC_PHINIT);
			}
			break;
#endif

		case 'E':
			if (BINLOAD_loading_basic) {
				ehopen_addr = MEMORY_dGetWord(devtab + Devices_TABLE_OPEN) + 1;
				ehclos_addr = MEMORY_dGetWord(devtab + Devices_TABLE_CLOS) + 1;
				ehread_addr = MEMORY_dGetWord(devtab + Devices_TABLE_READ) + 1;
				ehwrit_addr = MEMORY_dGetWord(devtab + Devices_TABLE_WRIT) + 1;
				ready_ptr = ready_prompt;
				ESC_AddEscRts(ehwrit_addr, ESC_EHWRIT, Devices_IgnoreReady);
				patched = TRUE;
			}
#ifdef BASIC
			else
				ESC_AddEscRts((UWORD) (MEMORY_dGetWord(devtab + Devices_TABLE_WRIT) + 1),
				                   ESC_EHWRIT, Devices_E_Write);
			ESC_AddEscRts((UWORD) (MEMORY_dGetWord(devtab + Devices_TABLE_READ) + 1),
			                   ESC_EHREAD, Devices_E_Read);
			patched = TRUE;
			break;
		case 'K':
			ESC_AddEscRts((UWORD) (MEMORY_dGetWord(devtab + Devices_TABLE_READ) + 1),
			                   ESC_KHREAD, Devices_K_Read);
			patched = TRUE;
			break;
#endif
		default:
			break;
		}
		addr += 3;				/* Next Device in HATABS */
	}
	return patched;
}
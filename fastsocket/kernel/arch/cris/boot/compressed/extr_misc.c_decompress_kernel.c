#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* ser3; void* ser2; void* ser1; int /*<<< orphan*/  sser_ser_dma6_7; } ;
typedef  TYPE_1__ reg_pinmux_rw_hwprot ;
typedef  TYPE_1__ reg_clkgen_rw_clk_ctrl ;

/* Variables and functions */
 TYPE_1__ REG_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int* R_GEN_CONFIG ; 
 int* R_SERIAL0_BAUD ; 
 int* R_SERIAL0_TR_CTRL ; 
 scalar_t__* R_SERIAL0_XOFF ; 
 int* R_SERIAL1_BAUD ; 
 int* R_SERIAL1_TR_CTRL ; 
 scalar_t__* R_SERIAL1_XOFF ; 
 int* R_SERIAL2_BAUD ; 
 int* R_SERIAL2_TR_CTRL ; 
 scalar_t__* R_SERIAL2_XOFF ; 
 int* R_SERIAL3_BAUD ; 
 int* R_SERIAL3_TR_CTRL ; 
 scalar_t__* R_SERIAL3_XOFF ; 
 int /*<<< orphan*/  clkgen ; 
 int /*<<< orphan*/  gunzip () ; 
 int /*<<< orphan*/  inbuf ; 
 int /*<<< orphan*/  input_data ; 
 int /*<<< orphan*/  makecrc () ; 
 int /*<<< orphan*/  pinmux ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  regi_clkgen ; 
 int /*<<< orphan*/  regi_pinmux ; 
 int /*<<< orphan*/  regi_ser0 ; 
 int /*<<< orphan*/  regi_ser1 ; 
 int /*<<< orphan*/  regi_ser2 ; 
 int /*<<< orphan*/  regi_ser3 ; 
 int /*<<< orphan*/  regk_clkgen_yes ; 
 void* regk_pinmux_yes ; 
 int /*<<< orphan*/  rw_clk_ctrl ; 
 int /*<<< orphan*/  rw_hwprot ; 
 int /*<<< orphan*/  serial_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_normal_output_buffer () ; 

void decompress_kernel(void)
{
	char revision;
	char compile_rev;

#ifdef CONFIG_ETRAX_ARCH_V32
	/* Need at least a CRISv32 to run. */
	compile_rev = 32;
#if defined(CONFIG_ETRAX_DEBUG_PORT1) || \
    defined(CONFIG_ETRAX_DEBUG_PORT2) || \
    defined(CONFIG_ETRAX_DEBUG_PORT3)
	reg_pinmux_rw_hwprot hwprot;

#ifdef CONFIG_CRIS_MACH_ARTPEC3
	reg_clkgen_rw_clk_ctrl clk_ctrl;

	/* Enable corresponding clock region when serial 1..3 selected */

	clk_ctrl = REG_RD(clkgen, regi_clkgen, rw_clk_ctrl);
	clk_ctrl.sser_ser_dma6_7 = regk_clkgen_yes;
	REG_WR(clkgen, regi_clkgen, rw_clk_ctrl, clk_ctrl);
#endif

	/* pinmux setup for ports 1..3 */
	hwprot = REG_RD(pinmux, regi_pinmux, rw_hwprot);
#endif


#ifdef CONFIG_ETRAX_DEBUG_PORT0
	serial_setup(regi_ser0);
#endif
#ifdef CONFIG_ETRAX_DEBUG_PORT1
	hwprot.ser1 = regk_pinmux_yes;
	serial_setup(regi_ser1);
#endif
#ifdef CONFIG_ETRAX_DEBUG_PORT2
	hwprot.ser2 = regk_pinmux_yes;
	serial_setup(regi_ser2);
#endif
#ifdef CONFIG_ETRAX_DEBUG_PORT3
	hwprot.ser3 = regk_pinmux_yes;
	serial_setup(regi_ser3);
#endif
#if defined(CONFIG_ETRAX_DEBUG_PORT1) || \
    defined(CONFIG_ETRAX_DEBUG_PORT2) || \
    defined(CONFIG_ETRAX_DEBUG_PORT3)
	REG_WR(pinmux, regi_pinmux, rw_hwprot, hwprot);
#endif

	/* input_data is set in head.S */
	inbuf = input_data;
#else /* CRISv10 */
	/* Need at least a crisv10 to run. */
	compile_rev = 10;

	/* input_data is set in head.S */
	inbuf = input_data;

#ifdef CONFIG_ETRAX_DEBUG_PORT0
	*R_SERIAL0_XOFF = 0;
	*R_SERIAL0_BAUD = 0x99;
	*R_SERIAL0_TR_CTRL = 0x40;
#endif
#ifdef CONFIG_ETRAX_DEBUG_PORT1
	*R_SERIAL1_XOFF = 0;
	*R_SERIAL1_BAUD = 0x99;
	*R_SERIAL1_TR_CTRL = 0x40;
#endif
#ifdef CONFIG_ETRAX_DEBUG_PORT2
	*R_GEN_CONFIG = 0x08;
	*R_SERIAL2_XOFF = 0;
	*R_SERIAL2_BAUD = 0x99;
	*R_SERIAL2_TR_CTRL = 0x40;
#endif
#ifdef CONFIG_ETRAX_DEBUG_PORT3
	*R_GEN_CONFIG = 0x100;
	*R_SERIAL3_XOFF = 0;
	*R_SERIAL3_BAUD = 0x99;
	*R_SERIAL3_TR_CTRL = 0x40;
#endif
#endif

	setup_normal_output_buffer();

	makecrc();

	__asm__ volatile ("move $vr,%0" : "=rm" (revision));
	if (revision < compile_rev) {
#ifdef CONFIG_ETRAX_ARCH_V32
		puts("You need an ETRAX FS to run Linux 2.6/crisv32\n");
#else
		puts("You need an ETRAX 100LX to run linux 2.6\n");
#endif
		while(1);
	}

	puts("Uncompressing Linux...\n");
	gunzip();
	puts("Done. Now booting the kernel\n");
}
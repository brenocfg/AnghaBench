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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct section {int /*<<< orphan*/  scn; } ;
struct readelf {int (* dw_decode ) (int**,int) ;} ;
struct TYPE_3__ {int d_size; int* d_buf; } ;
typedef  TYPE_1__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_1__* elf_rawdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_mips_register_size (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int stub1 (int**,int) ; 
 int stub10 (int**,int) ; 
 int stub11 (int**,int) ; 
 int stub2 (int**,int) ; 
 int stub3 (int**,int) ; 
 int stub4 (int**,int) ; 
 int stub5 (int**,int) ; 
 int stub6 (int**,int) ; 
 int stub7 (int**,int) ; 
 int stub8 (int**,int) ; 
 int stub9 (int**,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
dump_mips_abiflags(struct readelf *re, struct section *s)
{
	Elf_Data *d;
	uint8_t *p;
	int elferr;
	uint32_t isa_ext, ases, flags1, flags2;
	uint16_t version;
	uint8_t isa_level, isa_rev, gpr_size, cpr1_size, cpr2_size, fp_abi;

	if ((d = elf_rawdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_rawdata failed: %s",
			    elf_errmsg(elferr));
		return;
	}
	if (d->d_size != 24) {
		warnx("invalid MIPS abiflags section size");
		return;
	}

	p = d->d_buf;
	version = re->dw_decode(&p, 2);
	printf("MIPS ABI Flags Version: %u", version);
	if (version != 0) {
		printf(" (unknown)\n\n");
		return;
	}
	printf("\n\n");

	isa_level = re->dw_decode(&p, 1);
	isa_rev = re->dw_decode(&p, 1);
	gpr_size = re->dw_decode(&p, 1);
	cpr1_size = re->dw_decode(&p, 1);
	cpr2_size = re->dw_decode(&p, 1);
	fp_abi = re->dw_decode(&p, 1);
	isa_ext = re->dw_decode(&p, 4);
	ases = re->dw_decode(&p, 4);
	flags1 = re->dw_decode(&p, 4);
	flags2 = re->dw_decode(&p, 4);

	printf("ISA: ");
	if (isa_rev <= 1)
		printf("MIPS%u\n", isa_level);
	else
		printf("MIPS%ur%u\n", isa_level, isa_rev);
	printf("GPR size: %d\n", get_mips_register_size(gpr_size));
	printf("CPR1 size: %d\n", get_mips_register_size(cpr1_size));
	printf("CPR2 size: %d\n", get_mips_register_size(cpr2_size));
	printf("FP ABI: ");
	switch (fp_abi) {
	case 3:
		printf("Soft float");
		break;
	default:
		printf("%u", fp_abi);
		break;
	}
	printf("\nISA Extension: %u\n", isa_ext);
	printf("ASEs: %u\n", ases);
	printf("FLAGS 1: %08x\n", flags1);
	printf("FLAGS 2: %08x\n", flags2);
}
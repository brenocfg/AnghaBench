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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct section {char* name; int /*<<< orphan*/  scn; } ;
struct readelf {int (* dw_decode ) (int**,int) ;} ;
struct TYPE_3__ {scalar_t__ d_size; int* d_buf; } ;
typedef  TYPE_1__ Elf_Data ;

/* Variables and functions */
#define  ODK_EXCEPTIONS 138 
#define  ODK_FILL 137 
#define  ODK_GP_GROUP 136 
#define  ODK_HWAND 135 
#define  ODK_HWOR 134 
#define  ODK_HWPATCH 133 
#define  ODK_IDENT 132 
#define  ODK_PAD 131 
#define  ODK_PAGESIZE 130 
#define  ODK_REGINFO 129 
#define  ODK_TAGS 128 
 int OEX_FPU_MAX ; 
 int OEX_FPU_MIN ; 
 int /*<<< orphan*/  dump_mips_odk_reginfo (struct readelf*,int*,int) ; 
 int /*<<< orphan*/  dump_mips_option_flags (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_1__* elf_rawdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_exceptions_option ; 
 int /*<<< orphan*/  mips_hwa_option ; 
 int /*<<< orphan*/  mips_hwo_option ; 
 int /*<<< orphan*/  mips_hwpatch_option ; 
 int /*<<< orphan*/  mips_pad_option ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int stub1 (int**,int) ; 
 int stub2 (int**,int) ; 
 int stub3 (int**,int) ; 
 int stub4 (int**,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
dump_mips_options(struct readelf *re, struct section *s)
{
	Elf_Data *d;
	uint32_t info;
	uint16_t sndx;
	uint8_t *p, *pe;
	uint8_t kind, size;
	int elferr;

	(void) elf_errno();
	if ((d = elf_rawdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_rawdata failed: %s",
			    elf_errmsg(elferr));
		return;
	}
	if (d->d_size == 0)
		return;

	printf("\nSection %s contains:\n", s->name);
	p = d->d_buf;
	pe = p + d->d_size;
	while (p < pe) {
		if (pe - p < 8) {
			warnx("Truncated MIPS option header");
			return;
		}
		kind = re->dw_decode(&p, 1);
		size = re->dw_decode(&p, 1);
		sndx = re->dw_decode(&p, 2);
		info = re->dw_decode(&p, 4);
		if (size < 8 || size - 8 > pe - p) {
			warnx("Malformed MIPS option header");
			return;
		}
		size -= 8;
		switch (kind) {
		case ODK_REGINFO:
			dump_mips_odk_reginfo(re, p, size);
			break;
		case ODK_EXCEPTIONS:
			printf(" EXCEPTIONS FPU_MIN: %#x\n",
			    info & OEX_FPU_MIN);
			printf("%11.11s FPU_MAX: %#x\n", "",
			    info & OEX_FPU_MAX);
			dump_mips_option_flags("", mips_exceptions_option,
			    info);
			break;
		case ODK_PAD:
			printf(" %-10.10s section: %ju\n", "OPAD",
			    (uintmax_t) sndx);
			dump_mips_option_flags("", mips_pad_option, info);
			break;
		case ODK_HWPATCH:
			dump_mips_option_flags("HWPATCH", mips_hwpatch_option,
			    info);
			break;
		case ODK_HWAND:
			dump_mips_option_flags("HWAND", mips_hwa_option, info);
			break;
		case ODK_HWOR:
			dump_mips_option_flags("HWOR", mips_hwo_option, info);
			break;
		case ODK_FILL:
			printf(" %-10.10s %#jx\n", "FILL", (uintmax_t) info);
			break;
		case ODK_TAGS:
			printf(" %-10.10s\n", "TAGS");
			break;
		case ODK_GP_GROUP:
			printf(" %-10.10s GP group number: %#x\n", "GP_GROUP",
			    info & 0xFFFF);
			if (info & 0x10000)
				printf(" %-10.10s GP group is "
				    "self-contained\n", "");
			break;
		case ODK_IDENT:
			printf(" %-10.10s default GP group number: %#x\n",
			    "IDENT", info & 0xFFFF);
			if (info & 0x10000)
				printf(" %-10.10s default GP group is "
				    "self-contained\n", "");
			break;
		case ODK_PAGESIZE:
			printf(" %-10.10s\n", "PAGESIZE");
			break;
		default:
			break;
		}
		p += size;
	}
}
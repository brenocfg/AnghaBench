#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char* uintmax_t ;
typedef  char uint8_t ;
typedef  scalar_t__ uint64_t ;
struct section {scalar_t__ type; int /*<<< orphan*/  scn; } ;
struct TYPE_4__ {scalar_t__ e_machine; } ;
struct readelf {size_t shnum; size_t (* dw_decode ) (char**,int) ;TYPE_1__ ehdr; struct section* sl; } ;
struct TYPE_5__ {int d_size; char* d_buf; } ;
typedef  TYPE_2__ Elf_Data ;

/* Variables and functions */
 scalar_t__ EM_ARM ; 
 scalar_t__ EM_MIPS ; 
 scalar_t__ EM_MIPS_RS3_LE ; 
 scalar_t__ EM_PPC ; 
 scalar_t__ SHT_GNU_ATTRIBUTES ; 
 scalar_t__ SHT_LOPROC ; 
 scalar_t__ _decode_uleb128 (char**,char*) ; 
 int /*<<< orphan*/  dump_arm_attributes (struct readelf*,char*,char*) ; 
 int /*<<< orphan*/  dump_mips_attributes (struct readelf*,char*,char*) ; 
 int /*<<< orphan*/  dump_ppc_attributes (char*,char*) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_2__* elf_rawdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int strlen (char*) ; 
 size_t stub1 (char**,int) ; 
 size_t stub2 (char**,int) ; 
 char* top_tag (int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
dump_attributes(struct readelf *re)
{
	struct section *s;
	Elf_Data *d;
	uint8_t *p, *pe, *sp;
	size_t len, seclen, nlen, sublen;
	uint64_t val;
	int tag, i, elferr;

	for (i = 0; (size_t) i < re->shnum; i++) {
		s = &re->sl[i];
		if (s->type != SHT_GNU_ATTRIBUTES &&
		    (re->ehdr.e_machine != EM_ARM || s->type != SHT_LOPROC + 3))
			continue;
		(void) elf_errno();
		if ((d = elf_rawdata(s->scn, NULL)) == NULL) {
			elferr = elf_errno();
			if (elferr != 0)
				warnx("elf_rawdata failed: %s",
				    elf_errmsg(elferr));
			continue;
		}
		if (d->d_size <= 0)
			continue;
		p = d->d_buf;
		pe = p + d->d_size;
		if (*p != 'A') {
			printf("Unknown Attribute Section Format: %c\n",
			    (char) *p);
			continue;
		}
		len = d->d_size - 1;
		p++;
		while (len > 0) {
			if (len < 4) {
				warnx("truncated attribute section length");
				return;
			}
			seclen = re->dw_decode(&p, 4);
			if (seclen > len) {
				warnx("invalid attribute section length");
				return;
			}
			len -= seclen;
			nlen = strlen((char *) p) + 1;
			if (nlen + 4 > seclen) {
				warnx("invalid attribute section name");
				return;
			}
			printf("Attribute Section: %s\n", (char *) p);
			p += nlen;
			seclen -= nlen + 4;
			while (seclen > 0) {
				sp = p;
				tag = *p++;
				sublen = re->dw_decode(&p, 4);
				if (sublen > seclen) {
					warnx("invalid attribute sub-section"
					    " length");
					return;
				}
				seclen -= sublen;
				printf("%s", top_tag(tag));
				if (tag == 2 || tag == 3) {
					putchar(':');
					for (;;) {
						val = _decode_uleb128(&p, pe);
						if (val == 0)
							break;
						printf(" %ju", (uintmax_t) val);
					}
				}
				putchar('\n');
				if (re->ehdr.e_machine == EM_ARM &&
				    s->type == SHT_LOPROC + 3)
					dump_arm_attributes(re, p, sp + sublen);
				else if (re->ehdr.e_machine == EM_MIPS ||
				    re->ehdr.e_machine == EM_MIPS_RS3_LE)
					dump_mips_attributes(re, p,
					    sp + sublen);
				else if (re->ehdr.e_machine == EM_PPC)
					dump_ppc_attributes(p, sp + sublen);
				p = sp + sublen;
			}
		}
	}
}
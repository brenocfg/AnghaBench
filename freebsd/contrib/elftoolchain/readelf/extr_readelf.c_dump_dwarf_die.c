#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unk_tag ;
typedef  int /*<<< orphan*/  unk_attr ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint8_t ;
struct readelf {int /*<<< orphan*/  dbg; scalar_t__ (* dw_decode ) (int**,int) ;} ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_6__ {int* bl_data; scalar_t__ bl_len; } ;
struct TYPE_5__ {int /*<<< orphan*/ * signature; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  int Dwarf_Signed ;
typedef  TYPE_1__ Dwarf_Sig8 ;
typedef  int* Dwarf_Ptr ;
typedef  scalar_t__ Dwarf_Off ;
typedef  int Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Bool ;
typedef  TYPE_2__ Dwarf_Block ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
#define  DW_AT_data_member_location 162 
#define  DW_AT_encoding 161 
#define  DW_AT_frame_base 160 
 int DW_AT_high_pc ; 
#define  DW_AT_language 159 
#define  DW_AT_location 158 
#define  DW_AT_return_addr 157 
#define  DW_AT_segment 156 
#define  DW_AT_static_link 155 
#define  DW_AT_string_length 154 
#define  DW_AT_use_location 153 
#define  DW_AT_vtable_elem_location 152 
 int /*<<< orphan*/  DW_DLA_DIE ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
#define  DW_FORM_addr 151 
#define  DW_FORM_block 150 
#define  DW_FORM_block1 149 
#define  DW_FORM_block2 148 
#define  DW_FORM_block4 147 
#define  DW_FORM_data1 146 
#define  DW_FORM_data2 145 
#define  DW_FORM_data4 144 
#define  DW_FORM_data8 143 
#define  DW_FORM_exprloc 142 
#define  DW_FORM_flag 141 
#define  DW_FORM_flag_present 140 
#define  DW_FORM_ref1 139 
#define  DW_FORM_ref2 138 
#define  DW_FORM_ref4 137 
#define  DW_FORM_ref8 136 
#define  DW_FORM_ref_addr 135 
#define  DW_FORM_ref_sig8 134 
#define  DW_FORM_ref_udata 133 
#define  DW_FORM_sdata 132 
#define  DW_FORM_sec_offset 131 
#define  DW_FORM_string 130 
#define  DW_FORM_strp 129 
#define  DW_FORM_udata 128 
 int /*<<< orphan*/  dump_dwarf_block (struct readelf*,int*,scalar_t__) ; 
 int dwarf_attrlist (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int dwarf_attroffset (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_attrval_unsigned (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dwarf_die_CU_offset_range (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_die_abbrev_code (int /*<<< orphan*/ ) ; 
 int dwarf_dieoffset (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 int dwarf_formaddr (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_formblock (int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int dwarf_formexprloc (int /*<<< orphan*/ ,scalar_t__*,int**,int /*<<< orphan*/ *) ; 
 int dwarf_formflag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_formref (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_formsdata (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int dwarf_formsig8 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int dwarf_formstring (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int dwarf_formudata (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_get_ATE_name (scalar_t__,char const**) ; 
 int dwarf_get_AT_name (int,char const**) ; 
 int dwarf_get_LANG_name (scalar_t__,char const**) ; 
 int dwarf_get_TAG_name (int,char const**) ; 
 int /*<<< orphan*/  dwarf_get_die_infotypes_flag (int /*<<< orphan*/ ) ; 
 int dwarf_global_formref (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_siblingof_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dwarf_tag (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int dwarf_whatattr (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int dwarf_whatform (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 size_t strlen (char*) ; 
 scalar_t__ stub1 (int**,int) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_dwarf_die(struct readelf *re, Dwarf_Die die, int level)
{
	Dwarf_Attribute *attr_list;
	Dwarf_Die ret_die;
	Dwarf_Off dieoff, cuoff, culen, attroff;
	Dwarf_Unsigned ate, lang, v_udata, v_sig;
	Dwarf_Signed attr_count, v_sdata;
	Dwarf_Off v_off;
	Dwarf_Addr v_addr;
	Dwarf_Half tag, attr, form;
	Dwarf_Block *v_block;
	Dwarf_Bool v_bool, is_info;
	Dwarf_Sig8 v_sig8;
	Dwarf_Error de;
	Dwarf_Ptr v_expr;
	const char *tag_str, *attr_str, *ate_str, *lang_str;
	char unk_tag[32], unk_attr[32];
	char *v_str;
	uint8_t *b, *p;
	int i, j, abc, ret;

	if (dwarf_dieoffset(die, &dieoff, &de) != DW_DLV_OK) {
		warnx("dwarf_dieoffset failed: %s", dwarf_errmsg(de));
		goto cont_search;
	}

	printf(" <%d><%jx>: ", level, (uintmax_t) dieoff);

	if (dwarf_die_CU_offset_range(die, &cuoff, &culen, &de) != DW_DLV_OK) {
		warnx("dwarf_die_CU_offset_range failed: %s",
		      dwarf_errmsg(de));
		cuoff = 0;
	}

	abc = dwarf_die_abbrev_code(die);
	if (dwarf_tag(die, &tag, &de) != DW_DLV_OK) {
		warnx("dwarf_tag failed: %s", dwarf_errmsg(de));
		goto cont_search;
	}
	if (dwarf_get_TAG_name(tag, &tag_str) != DW_DLV_OK) {
		snprintf(unk_tag, sizeof(unk_tag), "[Unknown Tag: %#x]", tag);
		tag_str = unk_tag;
	}

	printf("Abbrev Number: %d (%s)\n", abc, tag_str);

	if ((ret = dwarf_attrlist(die, &attr_list, &attr_count, &de)) !=
	    DW_DLV_OK) {
		if (ret == DW_DLV_ERROR)
			warnx("dwarf_attrlist failed: %s", dwarf_errmsg(de));
		goto cont_search;
	}

	for (i = 0; i < attr_count; i++) {
		if (dwarf_whatform(attr_list[i], &form, &de) != DW_DLV_OK) {
			warnx("dwarf_whatform failed: %s", dwarf_errmsg(de));
			continue;
		}
		if (dwarf_whatattr(attr_list[i], &attr, &de) != DW_DLV_OK) {
			warnx("dwarf_whatattr failed: %s", dwarf_errmsg(de));
			continue;
		}
		if (dwarf_get_AT_name(attr, &attr_str) != DW_DLV_OK) {
			snprintf(unk_attr, sizeof(unk_attr),
			    "[Unknown AT: %#x]", attr);
			attr_str = unk_attr;
		}
		if (dwarf_attroffset(attr_list[i], &attroff, &de) !=
		    DW_DLV_OK) {
			warnx("dwarf_attroffset failed: %s", dwarf_errmsg(de));
			attroff = 0;
		}
		printf("    <%jx>   %-18s: ", (uintmax_t) attroff, attr_str);
		switch (form) {
		case DW_FORM_ref_addr:
		case DW_FORM_sec_offset:
			if (dwarf_global_formref(attr_list[i], &v_off, &de) !=
			    DW_DLV_OK) {
				warnx("dwarf_global_formref failed: %s",
				    dwarf_errmsg(de));
				continue;
			}
			if (form == DW_FORM_ref_addr)
				printf("<0x%jx>", (uintmax_t) v_off);
			else
				printf("0x%jx", (uintmax_t) v_off);
			break;

		case DW_FORM_ref1:
		case DW_FORM_ref2:
		case DW_FORM_ref4:
		case DW_FORM_ref8:
		case DW_FORM_ref_udata:
			if (dwarf_formref(attr_list[i], &v_off, &de) !=
			    DW_DLV_OK) {
				warnx("dwarf_formref failed: %s",
				    dwarf_errmsg(de));
				continue;
			}
			v_off += cuoff;
			printf("<0x%jx>", (uintmax_t) v_off);
			break;

		case DW_FORM_addr:
			if (dwarf_formaddr(attr_list[i], &v_addr, &de) !=
			    DW_DLV_OK) {
				warnx("dwarf_formaddr failed: %s",
				    dwarf_errmsg(de));
				continue;
			}
			printf("%#jx", (uintmax_t) v_addr);
			break;

		case DW_FORM_data1:
		case DW_FORM_data2:
		case DW_FORM_data4:
		case DW_FORM_data8:
		case DW_FORM_udata:
			if (dwarf_formudata(attr_list[i], &v_udata, &de) !=
			    DW_DLV_OK) {
				warnx("dwarf_formudata failed: %s",
				    dwarf_errmsg(de));
				continue;
			}
			if (attr == DW_AT_high_pc)
				printf("0x%jx", (uintmax_t) v_udata);
			else
				printf("%ju", (uintmax_t) v_udata);
			break;

		case DW_FORM_sdata:
			if (dwarf_formsdata(attr_list[i], &v_sdata, &de) !=
			    DW_DLV_OK) {
				warnx("dwarf_formudata failed: %s",
				    dwarf_errmsg(de));
				continue;
			}
			printf("%jd", (intmax_t) v_sdata);
			break;

		case DW_FORM_flag:
			if (dwarf_formflag(attr_list[i], &v_bool, &de) !=
			    DW_DLV_OK) {
				warnx("dwarf_formflag failed: %s",
				    dwarf_errmsg(de));
				continue;
			}
			printf("%jd", (intmax_t) v_bool);
			break;

		case DW_FORM_flag_present:
			putchar('1');
			break;

		case DW_FORM_string:
		case DW_FORM_strp:
			if (dwarf_formstring(attr_list[i], &v_str, &de) !=
			    DW_DLV_OK) {
				warnx("dwarf_formstring failed: %s",
				    dwarf_errmsg(de));
				continue;
			}
			if (form == DW_FORM_string)
				printf("%s", v_str);
			else
				printf("(indirect string) %s", v_str);
			break;

		case DW_FORM_block:
		case DW_FORM_block1:
		case DW_FORM_block2:
		case DW_FORM_block4:
			if (dwarf_formblock(attr_list[i], &v_block, &de) !=
			    DW_DLV_OK) {
				warnx("dwarf_formblock failed: %s",
				    dwarf_errmsg(de));
				continue;
			}
			printf("%ju byte block:", (uintmax_t) v_block->bl_len);
			b = v_block->bl_data;
			for (j = 0; (Dwarf_Unsigned) j < v_block->bl_len; j++)
				printf(" %x", b[j]);
			printf("\t(");
			dump_dwarf_block(re, v_block->bl_data, v_block->bl_len);
			putchar(')');
			break;

		case DW_FORM_exprloc:
			if (dwarf_formexprloc(attr_list[i], &v_udata, &v_expr,
			    &de) != DW_DLV_OK) {
				warnx("dwarf_formexprloc failed: %s",
				    dwarf_errmsg(de));
				continue;
			}
			printf("%ju byte block:", (uintmax_t) v_udata);
			b = v_expr;
			for (j = 0; (Dwarf_Unsigned) j < v_udata; j++)
				printf(" %x", b[j]);
			printf("\t(");
			dump_dwarf_block(re, v_expr, v_udata);
			putchar(')');
			break;

		case DW_FORM_ref_sig8:
			if (dwarf_formsig8(attr_list[i], &v_sig8, &de) !=
			    DW_DLV_OK) {
				warnx("dwarf_formsig8 failed: %s",
				    dwarf_errmsg(de));
				continue;
			}
			p = (uint8_t *)(uintptr_t) &v_sig8.signature[0];
			v_sig = re->dw_decode(&p, 8);
			printf("signature: 0x%jx", (uintmax_t) v_sig);
		}
		switch (attr) {
		case DW_AT_encoding:
			if (dwarf_attrval_unsigned(die, attr, &ate, &de) !=
			    DW_DLV_OK)
				break;
			if (dwarf_get_ATE_name(ate, &ate_str) != DW_DLV_OK)
				ate_str = "DW_ATE_UNKNOWN";
			printf("\t(%s)", &ate_str[strlen("DW_ATE_")]);
			break;

		case DW_AT_language:
			if (dwarf_attrval_unsigned(die, attr, &lang, &de) !=
			    DW_DLV_OK)
				break;
			if (dwarf_get_LANG_name(lang, &lang_str) != DW_DLV_OK)
				break;
			printf("\t(%s)", &lang_str[strlen("DW_LANG_")]);
			break;

		case DW_AT_location:
		case DW_AT_string_length:
		case DW_AT_return_addr:
		case DW_AT_data_member_location:
		case DW_AT_frame_base:
		case DW_AT_segment:
		case DW_AT_static_link:
		case DW_AT_use_location:
		case DW_AT_vtable_elem_location:
			switch (form) {
			case DW_FORM_data4:
			case DW_FORM_data8:
			case DW_FORM_sec_offset:
				printf("\t(location list)");
				break;
			default:
				break;
			}

		default:
			break;
		}
		putchar('\n');
	}


cont_search:
	/* Search children. */
	ret = dwarf_child(die, &ret_die, &de);
	if (ret == DW_DLV_ERROR)
		warnx("dwarf_child: %s", dwarf_errmsg(de));
	else if (ret == DW_DLV_OK)
		dump_dwarf_die(re, ret_die, level + 1);

	/* Search sibling. */
	is_info = dwarf_get_die_infotypes_flag(die);
	ret = dwarf_siblingof_b(re->dbg, die, &ret_die, is_info, &de);
	if (ret == DW_DLV_ERROR)
		warnx("dwarf_siblingof: %s", dwarf_errmsg(de));
	else if (ret == DW_DLV_OK)
		dump_dwarf_die(re, ret_die, level);

	dwarf_dealloc(re->dbg, die, DW_DLA_DIE);
}
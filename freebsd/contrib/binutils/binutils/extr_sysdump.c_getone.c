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
struct IT_un {int dummy; } ;
struct IT_sh {int dummy; } ;
struct IT_sc {int dummy; } ;
struct IT_rl {int dummy; } ;
struct IT_ob {int dummy; } ;
struct IT_hs {int dummy; } ;
struct IT_hd {int /*<<< orphan*/  afl; } ;
struct IT_er {int dummy; } ;
struct IT_ed {int dummy; } ;
struct IT_dus {int dummy; } ;
struct IT_dul {int dummy; } ;
struct IT_du {int dummy; } ;
struct IT_dty {int dummy; } ;
struct IT_dsy {int dummy; } ;
struct IT_dss {int dummy; } ;
struct IT_dso {int dummy; } ;
struct IT_dpt {int dummy; } ;
struct IT_dps {int dummy; } ;
struct IT_dln {int dummy; } ;
struct IT_dfp {int dummy; } ;
struct IT_den {int dummy; } ;
struct IT_dds {int dummy; } ;
struct IT_dbt {int dummy; } ;
struct IT_dar {int dummy; } ;
struct IT_cs {int dummy; } ;

/* Variables and functions */
#define  IT_cs_CODE 153 
#define  IT_dar_CODE 152 
#define  IT_dbt_CODE 151 
#define  IT_dds_CODE 150 
#define  IT_den_CODE 149 
#define  IT_dfp_CODE 148 
#define  IT_dln_CODE 147 
#define  IT_dps_CODE 146 
#define  IT_dpt_CODE 145 
#define  IT_dso_CODE 144 
#define  IT_dss_CODE 143 
#define  IT_dsy_CODE 142 
#define  IT_dty_CODE 141 
#define  IT_du_CODE 140 
#define  IT_dul_CODE 139 
#define  IT_dus_CODE 138 
#define  IT_ed_CODE 137 
#define  IT_er_CODE 136 
#define  IT_hd_CODE 135 
#define  IT_hs_CODE 134 
#define  IT_ob_CODE 133 
#define  IT_rl_CODE 132 
#define  IT_sc_CODE 131 
#define  IT_sh_CODE 130 
#define  IT_tr_CODE 129 
#define  IT_un_CODE 128 
 int /*<<< orphan*/  addrsize ; 
 int code ; 
 int /*<<< orphan*/  file ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sysroff_print_cs_out (struct IT_cs*) ; 
 int /*<<< orphan*/  sysroff_print_dar_out (struct IT_dar*) ; 
 int /*<<< orphan*/  sysroff_print_dbt_out (struct IT_dbt*) ; 
 int /*<<< orphan*/  sysroff_print_dds_out (struct IT_dds*) ; 
 int /*<<< orphan*/  sysroff_print_den_out (struct IT_den*) ; 
 int /*<<< orphan*/  sysroff_print_dfp_out (struct IT_dfp*) ; 
 int /*<<< orphan*/  sysroff_print_dln_out (struct IT_dln*) ; 
 int /*<<< orphan*/  sysroff_print_dps_out (struct IT_dps*) ; 
 int /*<<< orphan*/  sysroff_print_dpt_out (struct IT_dpt*) ; 
 int /*<<< orphan*/  sysroff_print_dso_out (struct IT_dso*) ; 
 int /*<<< orphan*/  sysroff_print_dss_out (struct IT_dss*) ; 
 int /*<<< orphan*/  sysroff_print_dsy_out (struct IT_dsy*) ; 
 int /*<<< orphan*/  sysroff_print_dty_out (struct IT_dty*) ; 
 int /*<<< orphan*/  sysroff_print_du_out (struct IT_du*) ; 
 int /*<<< orphan*/  sysroff_print_dul_out (struct IT_dul*) ; 
 int /*<<< orphan*/  sysroff_print_dus_out (struct IT_dus*) ; 
 int /*<<< orphan*/  sysroff_print_ed_out (struct IT_ed*) ; 
 int /*<<< orphan*/  sysroff_print_er_out (struct IT_er*) ; 
 int /*<<< orphan*/  sysroff_print_hd_out (struct IT_hd*) ; 
 int /*<<< orphan*/  sysroff_print_hs_out (struct IT_hs*) ; 
 int /*<<< orphan*/  sysroff_print_ob_out (struct IT_ob*) ; 
 int /*<<< orphan*/  sysroff_print_rl_out (struct IT_rl*) ; 
 int /*<<< orphan*/  sysroff_print_sc_out (struct IT_sc*) ; 
 int /*<<< orphan*/  sysroff_print_sh_out (struct IT_sh*) ; 
 int /*<<< orphan*/  sysroff_print_tr_out () ; 
 int /*<<< orphan*/  sysroff_print_un_out (struct IT_un*) ; 
 int /*<<< orphan*/  sysroff_swap_cs_in (struct IT_cs*) ; 
 int /*<<< orphan*/  sysroff_swap_dar_in (struct IT_dar*) ; 
 int /*<<< orphan*/  sysroff_swap_dbt_in (struct IT_dbt*) ; 
 int /*<<< orphan*/  sysroff_swap_dds_in (struct IT_dds*) ; 
 int /*<<< orphan*/  sysroff_swap_den_in (struct IT_den*) ; 
 int /*<<< orphan*/  sysroff_swap_dfp_in (struct IT_dfp*) ; 
 int /*<<< orphan*/  sysroff_swap_dln_in (struct IT_dln*) ; 
 int /*<<< orphan*/  sysroff_swap_dps_in (struct IT_dps*) ; 
 int /*<<< orphan*/  sysroff_swap_dpt_in (struct IT_dpt*) ; 
 int /*<<< orphan*/  sysroff_swap_dso_in (struct IT_dso*) ; 
 int /*<<< orphan*/  sysroff_swap_dss_in (struct IT_dss*) ; 
 int /*<<< orphan*/  sysroff_swap_dsy_in (struct IT_dsy*) ; 
 int /*<<< orphan*/  sysroff_swap_dty_in (struct IT_dty*) ; 
 int /*<<< orphan*/  sysroff_swap_du_in (struct IT_du*) ; 
 int /*<<< orphan*/  sysroff_swap_dul_in (struct IT_dul*) ; 
 int /*<<< orphan*/  sysroff_swap_dus_in (struct IT_dus*) ; 
 int /*<<< orphan*/  sysroff_swap_ed_in (struct IT_ed*) ; 
 int /*<<< orphan*/  sysroff_swap_er_in (struct IT_er*) ; 
 int /*<<< orphan*/  sysroff_swap_hd_in (struct IT_hd*) ; 
 int /*<<< orphan*/  sysroff_swap_hs_in (struct IT_hs*) ; 
 int /*<<< orphan*/  sysroff_swap_ob_in (struct IT_ob*) ; 
 int /*<<< orphan*/  sysroff_swap_rl_in (struct IT_rl*) ; 
 int /*<<< orphan*/  sysroff_swap_sc_in (struct IT_sc*) ; 
 int /*<<< orphan*/  sysroff_swap_sh_in (struct IT_sh*) ; 
 int /*<<< orphan*/  sysroff_swap_tr_in () ; 
 int /*<<< orphan*/  sysroff_swap_un_in (struct IT_un*) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getone (int type)
{
  int c = getc (file);

  code = c;

  if ((c & 0x7f) != type)
    {
      ungetc (c, file);
      return 0;
    }

  switch (c & 0x7f)
    {
    case IT_cs_CODE:
      {
	struct IT_cs dummy;
	sysroff_swap_cs_in (&dummy);
	sysroff_print_cs_out (&dummy);
      }
      break;

    case IT_dln_CODE:
      {
	struct IT_dln dummy;
	sysroff_swap_dln_in (&dummy);
	sysroff_print_dln_out (&dummy);
      }
      break;

    case IT_hd_CODE:
      {
	struct IT_hd dummy;
	sysroff_swap_hd_in (&dummy);
	addrsize = dummy.afl;
	sysroff_print_hd_out (&dummy);
      }
      break;

    case IT_dar_CODE:
      {
	struct IT_dar dummy;
	sysroff_swap_dar_in (&dummy);
	sysroff_print_dar_out (&dummy);
      }
      break;

    case IT_dsy_CODE:
      {
	struct IT_dsy dummy;
	sysroff_swap_dsy_in (&dummy);
	sysroff_print_dsy_out (&dummy);
      }
      break;

    case IT_dfp_CODE:
      {
	struct IT_dfp dummy;
	sysroff_swap_dfp_in (&dummy);
	sysroff_print_dfp_out (&dummy);
      }
      break;

    case IT_dso_CODE:
      {
	struct IT_dso dummy;
	sysroff_swap_dso_in (&dummy);
	sysroff_print_dso_out (&dummy);
      }
      break;

    case IT_dpt_CODE:
      {
	struct IT_dpt dummy;
	sysroff_swap_dpt_in (&dummy);
	sysroff_print_dpt_out (&dummy);
      }
      break;

    case IT_den_CODE:
      {
	struct IT_den dummy;
	sysroff_swap_den_in (&dummy);
	sysroff_print_den_out (&dummy);
      }
      break;

    case IT_dbt_CODE:
      {
	struct IT_dbt dummy;
	sysroff_swap_dbt_in (&dummy);
	sysroff_print_dbt_out (&dummy);
      }
      break;

    case IT_dty_CODE:
      {
	struct IT_dty dummy;
	sysroff_swap_dty_in (&dummy);
	sysroff_print_dty_out (&dummy);
      }
      break;

    case IT_un_CODE:
      {
	struct IT_un dummy;
	sysroff_swap_un_in (&dummy);
	sysroff_print_un_out (&dummy);
      }
      break;

    case IT_sc_CODE:
      {
	struct IT_sc dummy;
	sysroff_swap_sc_in (&dummy);
	sysroff_print_sc_out (&dummy);
      }
      break;

    case IT_er_CODE:
      {
	struct IT_er dummy;
	sysroff_swap_er_in (&dummy);
	sysroff_print_er_out (&dummy);
      }
      break;

    case IT_ed_CODE:
      {
	struct IT_ed dummy;
	sysroff_swap_ed_in (&dummy);
	sysroff_print_ed_out (&dummy);
      }
      break;

    case IT_sh_CODE:
      {
	struct IT_sh dummy;
	sysroff_swap_sh_in (&dummy);
	sysroff_print_sh_out (&dummy);
      }
      break;

    case IT_ob_CODE:
      {
	struct IT_ob dummy;
	sysroff_swap_ob_in (&dummy);
	sysroff_print_ob_out (&dummy);
      }
      break;

    case IT_rl_CODE:
      {
	struct IT_rl dummy;
	sysroff_swap_rl_in (&dummy);
	sysroff_print_rl_out (&dummy);
      }
      break;

    case IT_du_CODE:
      {
	struct IT_du dummy;
	sysroff_swap_du_in (&dummy);

	sysroff_print_du_out (&dummy);
      }
      break;

    case IT_dus_CODE:
      {
	struct IT_dus dummy;
	sysroff_swap_dus_in (&dummy);
	sysroff_print_dus_out (&dummy);
      }
      break;

    case IT_dul_CODE:
      {
	struct IT_dul dummy;
	sysroff_swap_dul_in (&dummy);
	sysroff_print_dul_out (&dummy);
      }
      break;

    case IT_dss_CODE:
      {
	struct IT_dss dummy;
	sysroff_swap_dss_in (&dummy);
	sysroff_print_dss_out (&dummy);
      }
      break;

    case IT_hs_CODE:
      {
	struct IT_hs dummy;
	sysroff_swap_hs_in (&dummy);
	sysroff_print_hs_out (&dummy);
      }
      break;

    case IT_dps_CODE:
      {
	struct IT_dps dummy;
	sysroff_swap_dps_in (&dummy);
	sysroff_print_dps_out (&dummy);
      }
      break;

    case IT_tr_CODE:
      sysroff_swap_tr_in ();
      sysroff_print_tr_out ();
      break;

    case IT_dds_CODE:
      {
	struct IT_dds dummy;

	sysroff_swap_dds_in (&dummy);
	sysroff_print_dds_out (&dummy);
      }
      break;

    default:
      printf ("GOT A %x\n", c);
      return 0;
      break;
    }

  return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buff ;
struct TYPE_4__ {int romsize; } ;
struct TYPE_3__ {int start; int end; int eeprom_type; int eeprom_bit_cl; int eeprom_bit_in; int eeprom_bit_out; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EL_STATUS ; 
 int /*<<< orphan*/  PQUIRK_FORCE_6BTN ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  PicoInitPico () ; 
 int /*<<< orphan*/  PicoQuirks ; 
 int /*<<< orphan*/  PicoSVPStartup () ; 
 int /*<<< orphan*/  SRF_EEPROM ; 
 int /*<<< orphan*/  SRF_ENABLED ; 
 TYPE_1__ SRam ; 
 char* builtin_carthw_cfg ; 
 int /*<<< orphan*/  carthw_Xin1_startup () ; 
 int /*<<< orphan*/  carthw_pier_startup () ; 
 int /*<<< orphan*/  carthw_prot_lk3_startup () ; 
 int /*<<< orphan*/  carthw_radica_startup () ; 
 int /*<<< orphan*/  carthw_realtec_startup () ; 
 int /*<<< orphan*/  carthw_sprot_new_location (int,int,int,int) ; 
 int /*<<< orphan*/  carthw_sprot_startup () ; 
 int /*<<< orphan*/  carthw_ssf2_startup () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int is_expr (char*,char**) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  parse_3_vals (char*,int*,int*,int*) ; 
 int rom_crc32 () ; 
 int rom_read32 (int) ; 
 scalar_t__ rom_strcmp (int,char*) ; 
 int /*<<< orphan*/  rstrip (char*) ; 
 char* sskip (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_carthw(const char *carthw_cfg, int *fill_sram)
{
  int line = 0, any_checks_passed = 0, skip_sect = 0;
  const char *s, *builtin = builtin_carthw_cfg;
  int tmp, rom_crc = 0;
  char buff[256], *p, *r;
  FILE *f;

  f = fopen(carthw_cfg, "r");
  if (f == NULL)
    f = fopen("pico/carthw.cfg", "r");
  if (f == NULL)
    elprintf(EL_STATUS, "couldn't open carthw.cfg!");

  for (;;)
  {
    if (f != NULL) {
      p = fgets(buff, sizeof(buff), f);
      if (p == NULL)
        break;
    }
    else {
      if (*builtin == 0)
        break;
      for (s = builtin; *s != 0 && *s != '\n'; s++)
        ;
      while (*s == '\n')
        s++;
      tmp = s - builtin;
      if (tmp > sizeof(buff) - 1)
        tmp = sizeof(buff) - 1;
      memcpy(buff, builtin, tmp);
      buff[tmp] = 0;
      p = buff;
      builtin = s;
    }

    line++;
    p = sskip(p);
    if (*p == 0 || *p == '#')
      continue;

    if (*p == '[') {
      any_checks_passed = 0;
      skip_sect = 0;
      continue;
    }
    
    if (skip_sect)
      continue;

    /* look for checks */
    if (is_expr("check_str", &p))
    {
      int offs;
      offs = strtoul(p, &r, 0);
      if (offs < 0 || offs > Pico.romsize) {
        elprintf(EL_STATUS, "carthw:%d: check_str offs out of range: %d\n", line, offs);
	goto bad;
      }
      p = sskip(r);
      if (*p != ',')
        goto bad;
      p = sskip(p + 1);
      if (*p != '"')
        goto bad;
      p++;
      r = strchr(p, '"');
      if (r == NULL)
        goto bad;
      *r = 0;

      if (rom_strcmp(offs, p) == 0)
        any_checks_passed = 1;
      else
        skip_sect = 1;
      continue;
    }
    else if (is_expr("check_size_gt", &p))
    {
      int size;
      size = strtoul(p, &r, 0);
      if (r == p || size < 0)
        goto bad;

      if (Pico.romsize > size)
        any_checks_passed = 1;
      else
        skip_sect = 1;
      continue;
    }
    else if (is_expr("check_csum", &p))
    {
      int csum;
      csum = strtoul(p, &r, 0);
      if (r == p || (csum & 0xffff0000))
        goto bad;

      if (csum == (rom_read32(0x18c) & 0xffff))
        any_checks_passed = 1;
      else
        skip_sect = 1;
      continue;
    }
    else if (is_expr("check_crc32", &p))
    {
      unsigned int crc;
      crc = strtoul(p, &r, 0);
      if (r == p)
        goto bad;

      if (rom_crc == 0)
        rom_crc = rom_crc32();
      if (crc == rom_crc)
        any_checks_passed = 1;
      else
        skip_sect = 1;
      continue;
    }

    /* now time for actions */
    if (is_expr("hw", &p)) {
      if (!any_checks_passed)
        goto no_checks;
      rstrip(p);

      if      (strcmp(p, "svp") == 0)
        PicoSVPStartup();
      else if (strcmp(p, "pico") == 0)
        PicoInitPico();
      else if (strcmp(p, "prot") == 0)
        carthw_sprot_startup();
      else if (strcmp(p, "ssf2_mapper") == 0)
        carthw_ssf2_startup();
      else if (strcmp(p, "x_in_1_mapper") == 0)
        carthw_Xin1_startup();
      else if (strcmp(p, "realtec_mapper") == 0)
        carthw_realtec_startup();
      else if (strcmp(p, "radica_mapper") == 0)
        carthw_radica_startup();
      else if (strcmp(p, "piersolar_mapper") == 0)
        carthw_pier_startup();
      else if (strcmp(p, "prot_lk3") == 0)
        carthw_prot_lk3_startup();
      else {
        elprintf(EL_STATUS, "carthw:%d: unsupported mapper: %s", line, p);
        skip_sect = 1;
      }
      continue;
    }
    if (is_expr("sram_range", &p)) {
      int start, end;

      if (!any_checks_passed)
        goto no_checks;
      rstrip(p);

      start = strtoul(p, &r, 0);
      if (r == p)
        goto bad;
      p = sskip(r);
      if (*p != ',')
        goto bad;
      p = sskip(p + 1);
      end = strtoul(p, &r, 0);
      if (r == p)
        goto bad;
      if (((start | end) & 0xff000000) || start > end) {
        elprintf(EL_STATUS, "carthw:%d: bad sram_range: %08x - %08x", line, start, end);
        goto bad_nomsg;
      }
      SRam.start = start;
      SRam.end = end;
      continue;
    }
    else if (is_expr("prop", &p)) {
      if (!any_checks_passed)
        goto no_checks;
      rstrip(p);

      if      (strcmp(p, "no_sram") == 0)
        SRam.flags &= ~SRF_ENABLED;
      else if (strcmp(p, "no_eeprom") == 0)
        SRam.flags &= ~SRF_EEPROM;
      else if (strcmp(p, "filled_sram") == 0)
        *fill_sram = 1;
      else if (strcmp(p, "force_6btn") == 0)
        PicoQuirks |= PQUIRK_FORCE_6BTN;
      else {
        elprintf(EL_STATUS, "carthw:%d: unsupported prop: %s", line, p);
        goto bad_nomsg;
      }
      elprintf(EL_STATUS, "game prop: %s", p);
      continue;
    }
    else if (is_expr("eeprom_type", &p)) {
      int type;
      if (!any_checks_passed)
        goto no_checks;
      rstrip(p);

      type = strtoul(p, &r, 0);
      if (r == p || type < 0)
        goto bad;
      SRam.eeprom_type = type;
      SRam.flags |= SRF_EEPROM;
      continue;
    }
    else if (is_expr("eeprom_lines", &p)) {
      int scl, sda_in, sda_out;
      if (!any_checks_passed)
        goto no_checks;
      rstrip(p);

      if (!parse_3_vals(p, &scl, &sda_in, &sda_out))
        goto bad;
      if (scl < 0 || scl > 15 || sda_in < 0 || sda_in > 15 ||
          sda_out < 0 || sda_out > 15)
        goto bad;

      SRam.eeprom_bit_cl = scl;
      SRam.eeprom_bit_in = sda_in;
      SRam.eeprom_bit_out= sda_out;
      continue;
    }
    else if ((tmp = is_expr("prot_ro_value16", &p)) || is_expr("prot_rw_value16", &p)) {
      int addr, mask, val;
      if (!any_checks_passed)
        goto no_checks;
      rstrip(p);

      if (!parse_3_vals(p, &addr, &mask, &val))
        goto bad;

      carthw_sprot_new_location(addr, mask, val, tmp ? 1 : 0);
      continue;
    }


bad:
    elprintf(EL_STATUS, "carthw:%d: unrecognized expression: %s", line, buff);
bad_nomsg:
    skip_sect = 1;
    continue;

no_checks:
    elprintf(EL_STATUS, "carthw:%d: command without any checks before it: %s", line, buff);
    skip_sect = 1;
    continue;
  }

  if (f != NULL)
    fclose(f);
}
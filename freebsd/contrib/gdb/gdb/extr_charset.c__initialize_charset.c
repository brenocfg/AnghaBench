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
typedef  int /*<<< orphan*/  tlist ;
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_set_enum_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ascii_print_literally ; 
 int /*<<< orphan*/  ascii_to_control ; 
 int /*<<< orphan*/  ascii_to_ebcdic_us_table ; 
 int /*<<< orphan*/  ascii_to_ibm1047_table ; 
 int /*<<< orphan*/  ascii_to_iso_8859_1_table ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  ebcdic_family_charset (char*) ; 
 int /*<<< orphan*/  ebcdic_us_to_ascii_table ; 
 int /*<<< orphan*/  ebcdic_us_to_ibm1047_table ; 
 int /*<<< orphan*/  ebcdic_us_to_iso_8859_1_table ; 
 int /*<<< orphan*/  host_charset_enum ; 
 int /*<<< orphan*/  host_charset_name ; 
 int /*<<< orphan*/  ibm1047_to_ascii_table ; 
 int /*<<< orphan*/  ibm1047_to_ebcdic_us_table ; 
 int /*<<< orphan*/  ibm1047_to_iso_8859_1_table ; 
 int /*<<< orphan*/  iso_8859_1_to_ascii_table ; 
 int /*<<< orphan*/  iso_8859_1_to_ebcdic_us_table ; 
 int /*<<< orphan*/  iso_8859_1_to_ibm1047_table ; 
 int /*<<< orphan*/  iso_8859_family_charset (char*) ; 
 int /*<<< orphan*/  register_charset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_iconv_charsets () ; 
 int /*<<< orphan*/  register_translation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_charset_sfunc ; 
 int /*<<< orphan*/  set_cmd_sfunc (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_host_charset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_host_charset_sfunc ; 
 int /*<<< orphan*/  set_target_charset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_target_charset_sfunc ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  show_charset ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  simple_charset (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_table_translation (char*,char*,int*) ; 
 int /*<<< orphan*/  target_charset_enum ; 
 int /*<<< orphan*/  target_charset_name ; 

void
_initialize_charset (void)
{
  struct cmd_list_element *new_cmd;

  /* Register all the character set GDB knows about.

     You should use the same names that iconv does, where possible, to
     take advantage of the iconv-based default behaviors.

     CAUTION: if you register a character set, you must also register
     as many translations as are necessary to make that character set
     interoperate correctly with all the other character sets.  We do
     provide default behaviors when no translation is available, or
     when a translation's function pointer for a particular operation
     is zero.  Hopefully, these defaults will be correct often enough
     that we won't need to provide too many translations.  */
  register_charset (simple_charset ("ASCII", 1,
                                    ascii_print_literally, 0,
                                    ascii_to_control, 0));
  register_charset (iso_8859_family_charset ("ISO-8859-1"));
  register_charset (ebcdic_family_charset ("EBCDIC-US"));
  register_charset (ebcdic_family_charset ("IBM1047"));
  register_iconv_charsets ();

  {
    struct { char *from; char *to; int *table; } tlist[] = {
      { "ASCII",      "ISO-8859-1", ascii_to_iso_8859_1_table },
      { "ASCII",      "EBCDIC-US",  ascii_to_ebcdic_us_table },
      { "ASCII",      "IBM1047",    ascii_to_ibm1047_table },
      { "ISO-8859-1", "ASCII",      iso_8859_1_to_ascii_table },
      { "ISO-8859-1", "EBCDIC-US",  iso_8859_1_to_ebcdic_us_table },
      { "ISO-8859-1", "IBM1047",    iso_8859_1_to_ibm1047_table },
      { "EBCDIC-US",  "ASCII",      ebcdic_us_to_ascii_table },
      { "EBCDIC-US",  "ISO-8859-1", ebcdic_us_to_iso_8859_1_table },
      { "EBCDIC-US",  "IBM1047",    ebcdic_us_to_ibm1047_table },
      { "IBM1047",    "ASCII",      ibm1047_to_ascii_table },
      { "IBM1047",    "ISO-8859-1", ibm1047_to_iso_8859_1_table },
      { "IBM1047",    "EBCDIC-US",  ibm1047_to_ebcdic_us_table }
    };

    int i;

    for (i = 0; i < (sizeof (tlist) / sizeof (tlist[0])); i++)
      register_translation (simple_table_translation (tlist[i].from,
                                                      tlist[i].to,
                                                      tlist[i].table));
  }

  set_host_charset (host_charset_name);
  set_target_charset (target_charset_name);

  new_cmd = add_set_enum_cmd ("charset",
			      class_support,
			      host_charset_enum,
			      &host_charset_name,
                              "Set the host and target character sets.\n"
                              "The `host character set' is the one used by the system GDB is running on.\n"
                              "The `target character set' is the one used by the program being debugged.\n"
                              "You may only use supersets of ASCII for your host character set; GDB does\n"
                              "not support any others.\n"
                              "To see a list of the character sets GDB supports, type `set charset <TAB>'.",
			      &setlist);

  /* Note that the sfunc below needs to set target_charset_name, because 
     the 'set charset' command sets two variables.  */
  set_cmd_sfunc (new_cmd, set_charset_sfunc);
  /* Don't use set_from_show - need to print some extra info. */
  add_cmd ("charset", class_support, show_charset,
	   "Show the host and target character sets.\n"
	   "The `host character set' is the one used by the system GDB is running on.\n"
	   "The `target character set' is the one used by the program being debugged.\n"
	   "You may only use supersets of ASCII for your host character set; GDB does\n"
	   "not support any others.\n"
	   "To see a list of the character sets GDB supports, type `set charset <TAB>'.", 
	   &showlist);


  new_cmd = add_set_enum_cmd ("host-charset",
			      class_support,
			      host_charset_enum,
			      &host_charset_name,
			      "Set the host character set.\n"
			      "The `host character set' is the one used by the system GDB is running on.\n"
			      "You may only use supersets of ASCII for your host character set; GDB does\n"
			      "not support any others.\n"
			      "To see a list of the character sets GDB supports, type `set host-charset <TAB>'.",
			      &setlist);

  set_cmd_sfunc (new_cmd, set_host_charset_sfunc);

  add_show_from_set (new_cmd, &showlist);



  new_cmd = add_set_enum_cmd ("target-charset",
			      class_support,
			      target_charset_enum,
			      &target_charset_name,
			      "Set the target character set.\n"
			      "The `target character set' is the one used by the program being debugged.\n"
			      "GDB translates characters and strings between the host and target\n"
			      "character sets as needed.\n"
			      "To see a list of the character sets GDB supports, type `set target-charset'<TAB>",
			      &setlist);

  set_cmd_sfunc (new_cmd, set_target_charset_sfunc);
  add_show_from_set (new_cmd, &showlist);
}
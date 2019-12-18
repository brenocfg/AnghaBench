#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cl_option {int flags; int /*<<< orphan*/  opt_text; } ;
typedef  enum opt_code { ____Placeholder_opt_code } opt_code ;
struct TYPE_10__ {scalar_t__ lang; } ;
struct TYPE_6__ {int missing_files; int phony_targets; void* style; } ;
struct TYPE_9__ {int print_include_names; int inhibit_warnings; int warn_trigraphs; int warn_comments; int warn_num_sign_change; int warn_multichar; int warn_deprecated; int warn_endif_labels; int warnings_are_errors; int warn_invalid_pch; int warn_missing_include_dirs; int warn_newline_at_eof; int warn_system_headers; int warn_traditional; int warn_undef; int directives_only; int dollars_in_ident; int extended_identifiers; int operator_names; int restore_pch_deps; int preprocessed; int show_column; int tabstop; char const* narrow_charset; char const* wide_charset; char const* input_charset; int objc; int pedantic_errors; int pedantic; int remap; int trigraphs; int traditional; int /*<<< orphan*/  warn_normalize; TYPE_1__ deps; int /*<<< orphan*/  discard_comments_in_macro_exp; int /*<<< orphan*/  discard_comments; } ;
struct TYPE_8__ {int warning_as_error_requested; } ;
struct TYPE_7__ {int inlines_hidden; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFTER ; 
 int /*<<< orphan*/  BRACKET ; 
 scalar_t__ CLK_ASM ; 
 int CL_C ; 
 int CL_CXX ; 
 int CL_Fortran ; 
 int CL_ObjC ; 
 int CL_ObjCXX ; 
 void* DEPS_SYSTEM ; 
 void* DEPS_USER ; 
#define  OPT_A 295 
#define  OPT_C 294 
#define  OPT_CC 293 
#define  OPT_D 292 
#define  OPT_E 291 
#define  OPT_F 290 
#define  OPT_H 289 
#define  OPT_I 288 
#define  OPT_M 287 
#define  OPT_MD 286 
#define  OPT_MF 285 
#define  OPT_MG 284 
#define  OPT_MM 283 
#define  OPT_MMD 282 
#define  OPT_MP 281 
#define  OPT_MQ 280 
#define  OPT_MT 279 
#define  OPT_P 278 
#define  OPT_U 277 
#define  OPT_Wall 276 
#define  OPT_Wcomment 275 
#define  OPT_Wcomments 274 
#define  OPT_Wdeprecated 273 
#define  OPT_Weffc__ 272 
#define  OPT_Wendif_labels 271 
#define  OPT_Werror 270 
#define  OPT_Werror_implicit_function_declaration 269 
#define  OPT_Wformat 268 
#define  OPT_Wformat_ 267 
#define  OPT_Wimplicit 266 
#define  OPT_Wimport 265 
#define  OPT_Winvalid_pch 264 
#define  OPT_Wmain 263 
#define  OPT_Wmissing_include_dirs 262 
#define  OPT_Wmost 261 
#define  OPT_Wmultichar 260 
#define  OPT_Wnewline_eof 259 
#define  OPT_Wnormalized_ 258 
#define  OPT_Wreturn_type 257 
#define  OPT_Wstrict_null_sentinel 256 
#define  OPT_Wsystem_headers 255 
#define  OPT_Wtraditional 254 
#define  OPT_Wtrigraphs 253 
#define  OPT_Wundef 252 
#define  OPT_Wunknown_pragmas 251 
#define  OPT_Wunused_macros 250 
#define  OPT_Wvariadic_macros 249 
#define  OPT_Wwrite_strings 248 
#define  OPT__output_pch_ 247 
#define  OPT_ansi 246 
#define  OPT_d 245 
#define  OPT_faccess_control 244 
#define  OPT_fall_virtual 243 
#define  OPT_falt_external_templates 242 
#define  OPT_fasm 241 
#define  OPT_fbuiltin 240 
#define  OPT_fbuiltin_ 239 
#define  OPT_fcheck_new 238 
#define  OPT_fcond_mismatch 237 
#define  OPT_fconserve_space 236 
#define  OPT_fconstant_string_class_ 235 
#define  OPT_fdefault_inline 234 
#define  OPT_fdirectives_only 233 
#define  OPT_fdollars_in_identifiers 232 
#define  OPT_felide_constructors 231 
#define  OPT_femit_struct_debug_baseonly 230 
#define  OPT_femit_struct_debug_detailed_ 229 
#define  OPT_femit_struct_debug_reduced 228 
#define  OPT_fenforce_eh_specs 227 
#define  OPT_fenum_int_equiv 226 
#define  OPT_fexec_charset_ 225 
#define  OPT_fextended_identifiers 224 
#define  OPT_fexternal_templates 223 
#define  OPT_ffor_scope 222 
#define  OPT_ffreestanding 221 
#define  OPT_fgnu_keywords 220 
#define  OPT_fgnu_runtime 219 
#define  OPT_fguiding_decls 218 
#define  OPT_fhandle_exceptions 217 
#define  OPT_fhonor_std 216 
#define  OPT_fhosted 215 
#define  OPT_fhuge_objects 214 
#define  OPT_fimplement_inlines 213 
#define  OPT_fimplicit_inline_templates 212 
#define  OPT_fimplicit_templates 211 
#define  OPT_finput_charset_ 210 
#define  OPT_flabels_ok 209 
#define  OPT_flax_vector_conversions 208 
#define  OPT_fms_extensions 207 
#define  OPT_fname_mangling_version_ 206 
#define  OPT_fnew_abi 205 
#define  OPT_fnext_runtime 204 
#define  OPT_fnil_receivers 203 
#define  OPT_fnonansi_builtins 202 
#define  OPT_fnonnull_objects 201 
#define  OPT_foperator_names 200 
#define  OPT_foptional_diags 199 
#define  OPT_fpch_deps 198 
#define  OPT_fpch_preprocess 197 
#define  OPT_fpermissive 196 
#define  OPT_fpreprocessed 195 
#define  OPT_freplace_objc_classes 194 
#define  OPT_frepo 193 
#define  OPT_frtti 192 
#define  OPT_fshort_double 191 
#define  OPT_fshort_enums 190 
#define  OPT_fshort_wchar 189 
#define  OPT_fshow_column 188 
#define  OPT_fsigned_bitfields 187 
#define  OPT_fsigned_char 186 
#define  OPT_fsquangle 185 
#define  OPT_fstats 184 
#define  OPT_fstrict_prototype 183 
#define  OPT_ftabstop_ 182 
#define  OPT_ftemplate_depth_ 181 
#define  OPT_fthis_is_variable 180 
#define  OPT_fthreadsafe_statics 179 
#define  OPT_funsigned_bitfields 178 
#define  OPT_funsigned_char 177 
#define  OPT_fuse_cxa_atexit 176 
#define  OPT_fuse_cxa_get_exception_ptr 175 
#define  OPT_fvisibility_inlines_hidden 174 
#define  OPT_fvtable_gc 173 
#define  OPT_fvtable_thunks 172 
#define  OPT_fweak 171 
#define  OPT_fwide_exec_charset_ 170 
#define  OPT_fworking_directory 169 
#define  OPT_fxref 168 
#define  OPT_fzero_link 167 
#define  OPT_gen_decls 166 
#define  OPT_idirafter 165 
#define  OPT_imacros 164 
#define  OPT_imultilib 163 
#define  OPT_include 162 
#define  OPT_iprefix 161 
#define  OPT_iquote 160 
#define  OPT_isysroot 159 
#define  OPT_isystem 158 
#define  OPT_iwithprefix 157 
#define  OPT_iwithprefixbefore 156 
#define  OPT_lang_asm 155 
#define  OPT_lang_fortran 154 
#define  OPT_lang_objc 153 
#define  OPT_nostdinc 152 
#define  OPT_nostdinc__ 151 
#define  OPT_o 150 
#define  OPT_pedantic 149 
#define  OPT_pedantic_errors 148 
#define  OPT_print_objc_runtime_info 147 
#define  OPT_print_pch_checksum 146 
#define  OPT_remap 145 
#define  OPT_std_c89 144 
#define  OPT_std_c99 143 
#define  OPT_std_c9x 142 
#define  OPT_std_c__98 141 
#define  OPT_std_gnu89 140 
#define  OPT_std_gnu99 139 
#define  OPT_std_gnu9x 138 
#define  OPT_std_gnu__98 137 
#define  OPT_std_iso9899_1990 136 
#define  OPT_std_iso9899_199409 135 
#define  OPT_std_iso9899_1999 134 
#define  OPT_std_iso9899_199x 133 
#define  OPT_traditional_cpp 132 
#define  OPT_trigraphs 131 
#define  OPT_undef 130 
#define  OPT_v 129 
#define  OPT_w 128 
 int /*<<< orphan*/  QUOTE ; 
 int /*<<< orphan*/  SYSTEM ; 
 int /*<<< orphan*/  TARGET_OPTF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_prefixed_path (char const*,int /*<<< orphan*/ ) ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  c_common_print_pch_checksum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_dialect_cxx () ; 
 struct cl_option* cl_options ; 
 char const* constant_string_class_name ; 
 TYPE_5__* cpp_get_options (int /*<<< orphan*/ ) ; 
 TYPE_4__* cpp_opts ; 
 int /*<<< orphan*/  cpp_set_lang (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  defer_opt (int,char const*) ; 
 char const* deps_file ; 
 int deps_seen ; 
 int /*<<< orphan*/  disable_builtin_function (char const*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int exit_after_options ; 
 int flag_access_control ; 
 int flag_check_new ; 
 int flag_cond_mismatch ; 
 int flag_conserve_space ; 
 int flag_default_inline ; 
 int flag_detailed_statistics ; 
 int flag_elide_constructors ; 
 int flag_enforce_eh_specs ; 
 int flag_exceptions ; 
 int flag_gen_declaration ; 
 int flag_hosted ; 
 int flag_implement_inlines ; 
 int flag_implicit_inline_templates ; 
 int flag_implicit_templates ; 
 int flag_lax_vector_conversions ; 
 int flag_ms_extensions ; 
 int flag_new_for_scope ; 
 int flag_next_runtime ; 
 int flag_nil_receivers ; 
 int flag_no_asm ; 
 int flag_no_builtin ; 
 int flag_no_gnu_keywords ; 
 int flag_no_line_commands ; 
 int flag_no_nonansi_builtin ; 
 int flag_no_output ; 
 int flag_optional_diags ; 
 int flag_pch_preprocess ; 
 int flag_permissive ; 
 int flag_preprocess_only ; 
 int flag_replace_objc_classes ; 
 int flag_rtti ; 
 int flag_short_double ; 
 int flag_short_enums ; 
 int flag_short_wchar ; 
 int flag_signed_bitfields ; 
 int flag_signed_char ; 
 int flag_threadsafe_statics ; 
 int flag_undef ; 
 int flag_use_cxa_atexit ; 
 int flag_use_cxa_get_exception_ptr ; 
 int flag_use_repository ; 
 int flag_weak ; 
 int flag_working_directory ; 
 int flag_zero_link ; 
 TYPE_3__* global_dc ; 
 int /*<<< orphan*/  handle_OPT_d (char const*) ; 
 char const* imultilib ; 
 int /*<<< orphan*/  inform (char*) ; 
 char const* iprefix ; 
 int lang_fortran ; 
 int max_tinst_depth ; 
 int mesg_implicit_function_declaration ; 
 int /*<<< orphan*/  normalized_C ; 
 int /*<<< orphan*/  normalized_KC ; 
 int /*<<< orphan*/  normalized_identifier_C ; 
 int /*<<< orphan*/  normalized_none ; 
 char const* out_fname ; 
 int /*<<< orphan*/  parse_in ; 
 char const* pch_file ; 
 int print_struct_values ; 
 int quote_chain_split ; 
 int /*<<< orphan*/  set_Wformat (int) ; 
 int /*<<< orphan*/  set_Wimplicit (int) ; 
 int /*<<< orphan*/  set_Wunused (int) ; 
 int /*<<< orphan*/  set_std_c89 (int,int) ; 
 int /*<<< orphan*/  set_std_c99 (int) ; 
 int /*<<< orphan*/  set_std_cxx98 (int) ; 
 int /*<<< orphan*/  set_struct_debug_option (char const*) ; 
 int /*<<< orphan*/  set_warn_strict_aliasing (int) ; 
 int /*<<< orphan*/  split_quote_chain () ; 
 int std_cxx_inc ; 
 int std_inc ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char const* sysroot ; 
 int verbose ; 
 TYPE_2__ visibility_options ; 
 int warn_address ; 
 int warn_char_subscripts ; 
 int warn_ecpp ; 
 int warn_main ; 
 int warn_missing_braces ; 
 int warn_nontemplate_friend ; 
 int warn_nonvdtor ; 
 int warn_overlength_strings ; 
 int warn_parentheses ; 
 int warn_pointer_sign ; 
 int warn_reorder ; 
 int warn_return_type ; 
 int warn_sequence_point ; 
 int warn_sign_compare ; 
 int warn_strict_null_sentinel ; 
 int warn_strict_overflow ; 
 int warn_switch ; 
 int warn_uninitialized ; 
 int warn_unknown_pragmas ; 
 int warn_unused_macros ; 
 int warn_variadic_macros ; 
 int warn_write_strings ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

int
c_common_handle_option (size_t scode, const char *arg, int value)
{
  const struct cl_option *option = &cl_options[scode];
  enum opt_code code = (enum opt_code) scode;
  int result = 1;

  /* Prevent resetting the language standard to a C dialect when the driver
     has already determined that we're looking at assembler input.  */
  bool preprocessing_asm_p = (cpp_get_options (parse_in)->lang == CLK_ASM);
 
  switch (code)
    {
    default:
      if (cl_options[code].flags & (CL_C | CL_CXX | CL_ObjC | CL_ObjCXX))
	break;
#ifdef CL_Fortran
      if (lang_fortran && (cl_options[code].flags & (CL_Fortran)))
	break;
#endif
      result = 0;
      break;

    case OPT__output_pch_:
      pch_file = arg;
      break;

    case OPT_A:
      defer_opt (code, arg);
      break;

    case OPT_C:
      cpp_opts->discard_comments = 0;
      break;

    case OPT_CC:
      cpp_opts->discard_comments = 0;
      cpp_opts->discard_comments_in_macro_exp = 0;
      break;

    case OPT_D:
      defer_opt (code, arg);
      break;

    case OPT_E:
      flag_preprocess_only = 1;
      break;

    case OPT_H:
      cpp_opts->print_include_names = 1;
      break;

    case OPT_F:
      TARGET_OPTF (xstrdup (arg));
      break;

    case OPT_I:
      if (strcmp (arg, "-"))
	add_path (xstrdup (arg), BRACKET, 0, true);
      else
	{
	  if (quote_chain_split)
	    error ("-I- specified twice");
	  quote_chain_split = true;
	  split_quote_chain ();
	  inform ("obsolete option -I- used, please use -iquote instead");
	}
      break;

    case OPT_M:
    case OPT_MM:
      /* When doing dependencies with -M or -MM, suppress normal
	 preprocessed output, but still do -dM etc. as software
	 depends on this.  Preprocessed output does occur if -MD, -MMD
	 or environment var dependency generation is used.  */
      cpp_opts->deps.style = (code == OPT_M ? DEPS_SYSTEM: DEPS_USER);
      flag_no_output = 1;
      cpp_opts->inhibit_warnings = 1;
      break;

    case OPT_MD:
    case OPT_MMD:
      cpp_opts->deps.style = (code == OPT_MD ? DEPS_SYSTEM: DEPS_USER);
      deps_file = arg;
      break;

    case OPT_MF:
      deps_seen = true;
      deps_file = arg;
      break;

    case OPT_MG:
      deps_seen = true;
      cpp_opts->deps.missing_files = true;
      break;

    case OPT_MP:
      deps_seen = true;
      cpp_opts->deps.phony_targets = true;
      break;

    case OPT_MQ:
    case OPT_MT:
      deps_seen = true;
      defer_opt (code, arg);
      break;

    case OPT_P:
      flag_no_line_commands = 1;
      break;

    case OPT_fworking_directory:
      flag_working_directory = value;
      break;

    case OPT_U:
      defer_opt (code, arg);
      break;

    case OPT_Wall:
      /* APPLE LOCAL -Wmost */
    case OPT_Wmost:
      set_Wunused (value);
      set_Wformat (value);
      set_Wimplicit (value);
      warn_char_subscripts = value;
      warn_missing_braces = value;
      /* APPLE LOCAL begin -Wmost --dpatel */
      if (code != OPT_Wmost) 
	warn_parentheses = value;
      /* APPLE LOCAL end -Wmost --dpatel */
      warn_return_type = value;
      warn_sequence_point = value;	/* Was C only.  */
      if (c_dialect_cxx ())
	warn_sign_compare = value;
      warn_switch = value;
      set_warn_strict_aliasing (value);
      warn_strict_overflow = value;
      warn_address = value;

      /* Only warn about unknown pragmas that are not in system
	 headers.  */
      warn_unknown_pragmas = value;

      /* We save the value of warn_uninitialized, since if they put
	 -Wuninitialized on the command line, we need to generate a
	 warning about not using it without also specifying -O.  */
      if (warn_uninitialized != 1)
	warn_uninitialized = (value ? 2 : 0);

      if (!c_dialect_cxx ())
	/* We set this to 2 here, but 1 in -Wmain, so -ffreestanding
	   can turn it off only if it's not explicit.  */
	warn_main = value * 2;
      else
	{
	  /* C++-specific warnings.  */
	  warn_reorder = value;
	  warn_nontemplate_friend = value;
	}

      cpp_opts->warn_trigraphs = value;
      cpp_opts->warn_comments = value;
      cpp_opts->warn_num_sign_change = value;
      cpp_opts->warn_multichar = value;	/* Was C++ only.  */

      if (warn_pointer_sign == -1)
	warn_pointer_sign = 1;
      break;

    case OPT_Wcomment:
    case OPT_Wcomments:
      cpp_opts->warn_comments = value;
      break;

    case OPT_Wdeprecated:
      cpp_opts->warn_deprecated = value;
      break;

    case OPT_Wendif_labels:
      cpp_opts->warn_endif_labels = value;
      break;

    case OPT_Werror:
      cpp_opts->warnings_are_errors = value;
      global_dc->warning_as_error_requested = value;
      break;

    case OPT_Werror_implicit_function_declaration:
      mesg_implicit_function_declaration = 2;
      break;

    case OPT_Wformat:
      set_Wformat (value);
      break;

    case OPT_Wformat_:
      set_Wformat (atoi (arg));
      break;

    case OPT_Wimplicit:
      set_Wimplicit (value);
      break;

    case OPT_Wimport:
      /* Silently ignore for now.  */
      break;

    case OPT_Winvalid_pch:
      cpp_opts->warn_invalid_pch = value;
      break;

    case OPT_Wmain:
      if (value)
	warn_main = 1;
      else
	warn_main = -1;
      break;

    case OPT_Wmissing_include_dirs:
      cpp_opts->warn_missing_include_dirs = value;
      break;

    case OPT_Wmultichar:
      cpp_opts->warn_multichar = value;
      break;

      /* APPLE LOCAL begin -Wnewline-eof */
    case OPT_Wnewline_eof:
      cpp_opts->warn_newline_at_eof = value;
      break;
      /* APPLE LOCAL end -Wnewline-eof */

    case OPT_Wnormalized_:
      if (!value || (arg && strcasecmp (arg, "none") == 0))
	cpp_opts->warn_normalize = normalized_none;
      else if (!arg || strcasecmp (arg, "nfkc") == 0)
	cpp_opts->warn_normalize = normalized_KC;
      else if (strcasecmp (arg, "id") == 0)
	cpp_opts->warn_normalize = normalized_identifier_C;
      else if (strcasecmp (arg, "nfc") == 0)
	cpp_opts->warn_normalize = normalized_C;
      else
	error ("argument %qs to %<-Wnormalized%> not recognized", arg);
      break;

    case OPT_Wreturn_type:
      warn_return_type = value;
      break;

    case OPT_Wstrict_null_sentinel:
      warn_strict_null_sentinel = value;
      break;

    case OPT_Wsystem_headers:
      cpp_opts->warn_system_headers = value;
      break;

    case OPT_Wtraditional:
      cpp_opts->warn_traditional = value;
      break;

    case OPT_Wtrigraphs:
      cpp_opts->warn_trigraphs = value;
      break;

    case OPT_Wundef:
      cpp_opts->warn_undef = value;
      break;

    case OPT_Wunknown_pragmas:
      /* Set to greater than 1, so that even unknown pragmas in
	 system headers will be warned about.  */
      warn_unknown_pragmas = value * 2;
      break;

    case OPT_Wunused_macros:
      warn_unused_macros = value;
      break;

    case OPT_Wvariadic_macros:
      warn_variadic_macros = value;
      break;

    case OPT_Wwrite_strings:
      warn_write_strings = value;
      break;

    case OPT_Weffc__:
      warn_ecpp = value;
      if (value)
        warn_nonvdtor = true;
      break;

    case OPT_ansi:
      if (!c_dialect_cxx ())
	set_std_c89 (false, true);
      else
	set_std_cxx98 (true);
      break;

    case OPT_d:
      handle_OPT_d (arg);
      break;

    case OPT_fcond_mismatch:
      if (!c_dialect_cxx ())
	{
	  flag_cond_mismatch = value;
	  break;
	}
      /* Fall through.  */

    case OPT_fall_virtual:
    case OPT_falt_external_templates:
    case OPT_fenum_int_equiv:
    case OPT_fexternal_templates:
    case OPT_fguiding_decls:
    case OPT_fhonor_std:
    case OPT_fhuge_objects:
    case OPT_flabels_ok:
    case OPT_fname_mangling_version_:
    case OPT_fnew_abi:
    case OPT_fnonnull_objects:
    case OPT_fsquangle:
    case OPT_fstrict_prototype:
    case OPT_fthis_is_variable:
    case OPT_fvtable_thunks:
    case OPT_fxref:
    case OPT_fvtable_gc:
      warning (0, "switch %qs is no longer supported", option->opt_text);
      break;

    case OPT_faccess_control:
      flag_access_control = value;
      break;

    case OPT_fasm:
      flag_no_asm = !value;
      break;

    case OPT_fbuiltin:
      flag_no_builtin = !value;
      break;

    case OPT_fbuiltin_:
      if (value)
	result = 0;
      else
	disable_builtin_function (arg);
      break;

    case OPT_fdirectives_only:
      cpp_opts->directives_only = 1;
      break;

    case OPT_fdollars_in_identifiers:
      cpp_opts->dollars_in_ident = value;
      break;

    case OPT_ffreestanding:
      value = !value;
      /* Fall through....  */
    case OPT_fhosted:
      flag_hosted = value;
      flag_no_builtin = !value;
      /* warn_main will be 2 if set by -Wall, 1 if set by -Wmain */
      if (!value && warn_main == 2)
	warn_main = 0;
      break;

    case OPT_fshort_double:
      flag_short_double = value;
      break;

    case OPT_fshort_enums:
      flag_short_enums = value;
      break;

    case OPT_fshort_wchar:
      flag_short_wchar = value;
      break;

    case OPT_fsigned_bitfields:
      flag_signed_bitfields = value;
      break;

    case OPT_fsigned_char:
      flag_signed_char = value;
      break;

    case OPT_funsigned_bitfields:
      flag_signed_bitfields = !value;
      break;

    case OPT_funsigned_char:
      flag_signed_char = !value;
      break;

    case OPT_fcheck_new:
      flag_check_new = value;
      break;

    case OPT_fconserve_space:
      flag_conserve_space = value;
      break;

    case OPT_fconstant_string_class_:
      constant_string_class_name = arg;
      break;

    case OPT_fdefault_inline:
      flag_default_inline = value;
      break;

    case OPT_felide_constructors:
      flag_elide_constructors = value;
      break;

    case OPT_fenforce_eh_specs:
      flag_enforce_eh_specs = value;
      break;

    case OPT_fextended_identifiers:
      cpp_opts->extended_identifiers = value;
      break;

    case OPT_ffor_scope:
      flag_new_for_scope = value;
      break;

    case OPT_fgnu_keywords:
      flag_no_gnu_keywords = !value;
      break;

    case OPT_fgnu_runtime:
      flag_next_runtime = !value;
      break;

    case OPT_fhandle_exceptions:
      warning (0, "-fhandle-exceptions has been renamed -fexceptions (and is now on by default)");
      flag_exceptions = value;
      break;

    case OPT_fimplement_inlines:
      flag_implement_inlines = value;
      break;

    case OPT_fimplicit_inline_templates:
      flag_implicit_inline_templates = value;
      break;

    case OPT_fimplicit_templates:
      flag_implicit_templates = value;
      break;

    case OPT_flax_vector_conversions:
      flag_lax_vector_conversions = value;
      break;

    case OPT_fms_extensions:
      flag_ms_extensions = value;
      break;

    case OPT_fnext_runtime:
      flag_next_runtime = value;
      break;

    case OPT_fnil_receivers:
      flag_nil_receivers = value;
      break;

    case OPT_fnonansi_builtins:
      flag_no_nonansi_builtin = !value;
      break;

    case OPT_foperator_names:
      cpp_opts->operator_names = value;
      break;

    case OPT_foptional_diags:
      flag_optional_diags = value;
      break;

    case OPT_fpch_deps:
      cpp_opts->restore_pch_deps = value;
      break;

    case OPT_fpch_preprocess:
      flag_pch_preprocess = value;
      break;

    case OPT_fpermissive:
      flag_permissive = value;
      break;

    case OPT_fpreprocessed:
      cpp_opts->preprocessed = value;
      break;

    case OPT_freplace_objc_classes:
      flag_replace_objc_classes = value;
      break;

    case OPT_frepo:
      flag_use_repository = value;
      if (value)
	flag_implicit_templates = 0;
      break;

    case OPT_frtti:
      flag_rtti = value;
      break;

    case OPT_fshow_column:
      cpp_opts->show_column = value;
      break;

    case OPT_fstats:
      flag_detailed_statistics = value;
      break;

    case OPT_ftabstop_:
      /* It is documented that we silently ignore silly values.  */
      if (value >= 1 && value <= 100)
	cpp_opts->tabstop = value;
      break;

    case OPT_fexec_charset_:
      cpp_opts->narrow_charset = arg;
      break;

    case OPT_fwide_exec_charset_:
      cpp_opts->wide_charset = arg;
      break;

    case OPT_finput_charset_:
      cpp_opts->input_charset = arg;
      break;

    case OPT_ftemplate_depth_:
      max_tinst_depth = value;
      break;

    case OPT_fuse_cxa_atexit:
      flag_use_cxa_atexit = value;
      break;
      
    case OPT_fuse_cxa_get_exception_ptr:
      flag_use_cxa_get_exception_ptr = value;
      break;

    case OPT_fvisibility_inlines_hidden:
      visibility_options.inlines_hidden = value;
      break;

    case OPT_fweak:
      flag_weak = value;
      break;

    case OPT_fthreadsafe_statics:
      flag_threadsafe_statics = value;
      break;

    case OPT_fzero_link:
      flag_zero_link = value;
      break;

    case OPT_gen_decls:
      flag_gen_declaration = 1;
      break;

    case OPT_femit_struct_debug_baseonly:
      set_struct_debug_option ("base");
      break;

    case OPT_femit_struct_debug_reduced:
      set_struct_debug_option ("dir:ord:sys,dir:gen:any,ind:base");
      break;

    case OPT_femit_struct_debug_detailed_:
      set_struct_debug_option (arg);
      break;

    case OPT_idirafter:
      add_path (xstrdup (arg), AFTER, 0, true);
      break;

    case OPT_imacros:
    case OPT_include:
      defer_opt (code, arg);
      break;

    case OPT_imultilib:
      imultilib = arg;
      break;

    case OPT_iprefix:
      iprefix = arg;
      break;

    case OPT_iquote:
      add_path (xstrdup (arg), QUOTE, 0, true);
      break;

    case OPT_isysroot:
      sysroot = arg;
      break;

    case OPT_isystem:
      add_path (xstrdup (arg), SYSTEM, 0, true);
      break;

    case OPT_iwithprefix:
      add_prefixed_path (arg, SYSTEM);
      break;

    case OPT_iwithprefixbefore:
      add_prefixed_path (arg, BRACKET);
      break;

    case OPT_lang_asm:
      cpp_set_lang (parse_in, CLK_ASM);
      cpp_opts->dollars_in_ident = false;
      break;

    case OPT_lang_fortran:
      lang_fortran = true;
      break;

    case OPT_lang_objc:
      cpp_opts->objc = 1;
      break;

    case OPT_nostdinc:
      std_inc = false;
      break;

    case OPT_nostdinc__:
      std_cxx_inc = false;
      break;

    case OPT_o:
      if (!out_fname)
	out_fname = arg;
      else
	error ("output filename specified twice");
      break;

      /* We need to handle the -pedantic switches here, rather than in
	 c_common_post_options, so that a subsequent -Wno-endif-labels
	 is not overridden.  */
    case OPT_pedantic_errors:
      cpp_opts->pedantic_errors = 1;
      /* Fall through.  */
    case OPT_pedantic:
      cpp_opts->pedantic = 1;
      cpp_opts->warn_endif_labels = 1;
      if (warn_pointer_sign == -1)
	warn_pointer_sign = 1;
      if (warn_overlength_strings == -1)
	warn_overlength_strings = 1;
      break;

    case OPT_print_objc_runtime_info:
      print_struct_values = 1;
      break;

    case OPT_print_pch_checksum:
      c_common_print_pch_checksum (stdout);
      exit_after_options = true;
      break;

    case OPT_remap:
      cpp_opts->remap = 1;
      break;

    case OPT_std_c__98:
    case OPT_std_gnu__98:
      if (!preprocessing_asm_p)
	set_std_cxx98 (code == OPT_std_c__98 /* ISO */);
      break;

    case OPT_std_c89:
    case OPT_std_iso9899_1990:
    case OPT_std_iso9899_199409:
      if (!preprocessing_asm_p)
	set_std_c89 (code == OPT_std_iso9899_199409 /* c94 */, true /* ISO */);
      break;

    case OPT_std_gnu89:
      if (!preprocessing_asm_p)
	set_std_c89 (false /* c94 */, false /* ISO */);
      break;

    case OPT_std_c99:
    case OPT_std_c9x:
    case OPT_std_iso9899_1999:
    case OPT_std_iso9899_199x:
      if (!preprocessing_asm_p)
	set_std_c99 (true /* ISO */);
      break;

    case OPT_std_gnu99:
    case OPT_std_gnu9x:
      if (!preprocessing_asm_p)
	set_std_c99 (false /* ISO */);
      break;

    case OPT_trigraphs:
      cpp_opts->trigraphs = 1;
      break;

    case OPT_traditional_cpp:
      cpp_opts->traditional = 1;
      break;

    case OPT_undef:
      flag_undef = 1;
      break;

    case OPT_w:
      cpp_opts->inhibit_warnings = 1;
      break;

    case OPT_v:
      verbose = true;
      break;
    }

  return result;
}
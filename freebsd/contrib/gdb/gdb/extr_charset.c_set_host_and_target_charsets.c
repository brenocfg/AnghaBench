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
struct translation {int /*<<< orphan*/ * convert_char_baton; void* convert_char; int /*<<< orphan*/  c_parse_backslash_baton; scalar_t__ c_parse_backslash; int /*<<< orphan*/  c_target_char_has_backslash_escape_baton; scalar_t__ c_target_char_has_backslash_escape; } ;
struct charset {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  c_parse_backslash_baton ; 
 scalar_t__ c_parse_backslash_func ; 
 int /*<<< orphan*/  c_target_char_has_backslash_escape_baton ; 
 scalar_t__ c_target_char_has_backslash_escape_func ; 
 int /*<<< orphan*/  cached_iconv_host_to_target ; 
 int /*<<< orphan*/  cached_iconv_target_to_host ; 
 scalar_t__ check_iconv_cache (int /*<<< orphan*/ *,struct charset*,struct charset*) ; 
 struct charset* current_host_charset ; 
 struct charset* current_target_charset ; 
 scalar_t__ default_c_parse_backslash ; 
 scalar_t__ default_c_target_char_has_backslash_escape ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/ * host_char_to_target_baton ; 
 void* host_char_to_target_func ; 
 void* iconv_convert ; 
 void* identity_either_char_to_other ; 
 struct translation* lookup_translation (char*,char*) ; 
 int /*<<< orphan*/ * target_char_to_host_baton ; 
 void* target_char_to_host_func ; 

__attribute__((used)) static void
set_host_and_target_charsets (struct charset *host, struct charset *target)
{
  struct translation *h2t, *t2h;

  /* If they're not both initialized yet, then just do nothing for
     now.  As soon as we're done running our initialize function,
     everything will be initialized.  */
  if (! host || ! target)
    {
      current_host_charset = host;
      current_target_charset = target;
      return;
    }

  h2t = lookup_translation (host->name, target->name);
  t2h = lookup_translation (target->name, host->name);

  /* If the translations don't provide conversion functions, make sure
     iconv can back them up.  Do this *before* modifying any state.  */
  if (host != target)
    {
      if (! h2t || ! h2t->convert_char)
        {
          if (check_iconv_cache (&cached_iconv_host_to_target, host, target)
              < 0)
            error ("GDB can't convert from the `%s' character set to `%s'.",
                   host->name, target->name);
        }
      if (! t2h || ! t2h->convert_char)
        {
          if (check_iconv_cache (&cached_iconv_target_to_host, target, host)
              < 0)
            error ("GDB can't convert from the `%s' character set to `%s'.",
                   target->name, host->name);
        }
    }

  if (t2h && t2h->c_target_char_has_backslash_escape)
    {
      c_target_char_has_backslash_escape_func
        = t2h->c_target_char_has_backslash_escape;
      c_target_char_has_backslash_escape_baton
        = t2h->c_target_char_has_backslash_escape_baton;
    }
  else
    c_target_char_has_backslash_escape_func
      = default_c_target_char_has_backslash_escape;

  if (h2t && h2t->c_parse_backslash)
    {
      c_parse_backslash_func = h2t->c_parse_backslash;
      c_parse_backslash_baton = h2t->c_parse_backslash_baton;
    }
  else
    c_parse_backslash_func = default_c_parse_backslash;

  if (h2t && h2t->convert_char)
    {
      host_char_to_target_func = h2t->convert_char;
      host_char_to_target_baton = h2t->convert_char_baton;
    }
  else if (host == target)
    host_char_to_target_func = identity_either_char_to_other;
  else
    {
      host_char_to_target_func = iconv_convert;
      host_char_to_target_baton = &cached_iconv_host_to_target;
    }

  if (t2h && t2h->convert_char)
    {
      target_char_to_host_func = t2h->convert_char;
      target_char_to_host_baton = t2h->convert_char_baton;
    }
  else if (host == target)
    target_char_to_host_func = identity_either_char_to_other;
  else
    {
      target_char_to_host_func = iconv_convert;
      target_char_to_host_baton = &cached_iconv_target_to_host;
    }

  current_host_charset = host;
  current_target_charset = target;
}
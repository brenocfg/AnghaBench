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
typedef  int /*<<< orphan*/  wchar_t ;
struct alias {unsigned int encoding_index; } ;

/* Variables and functions */
 int MAX_WORD_LENGTH ; 
 struct alias* aliases2_lookup (char*) ; 
 struct alias* aliases_lookup (char*,int) ; 
 int* all_canonical ; 
 unsigned int ei_iso8859_1 ; 
 unsigned int ei_local_char ; 
 unsigned int ei_local_wchar_t ; 
 unsigned int ei_ucs2internal ; 
 unsigned int ei_ucs4internal ; 
 char* locale_charset () ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 char* stringpool ; 
 char* stringpool2 ; 

const char * iconv_canonicalize (const char * name)
{
  const char* code;
  char buf[MAX_WORD_LENGTH+10+1];
  const char* cp;
  char* bp;
  const struct alias * ap;
  unsigned int count;
  unsigned int index;
  const char* pool;

  /* Before calling aliases_lookup, convert the input string to upper case,
   * and check whether it's entirely ASCII (we call gperf with option "-7"
   * to achieve a smaller table) and non-empty. If it's not entirely ASCII,
   * or if it's too long, it is not a valid encoding name.
   */
  for (code = name;;) {
    /* Search code in the table. */
    for (cp = code, bp = buf, count = MAX_WORD_LENGTH+10+1; ; cp++, bp++) {
      unsigned char c = * (unsigned char *) cp;
      if (c >= 0x80)
        goto invalid;
      if (c >= 'a' && c <= 'z')
        c -= 'a'-'A';
      *bp = c;
      if (c == '\0')
        break;
      if (--count == 0)
        goto invalid;
    }
    for (;;) {
      if (bp-buf >= 10 && memcmp(bp-10,"//TRANSLIT",10)==0) {
        bp -= 10;
        *bp = '\0';
        continue;
      }
      if (bp-buf >= 8 && memcmp(bp-8,"//IGNORE",8)==0) {
        bp -= 8;
        *bp = '\0';
        continue;
      }
      break;
    }
    if (buf[0] == '\0') {
      code = locale_charset();
      /* Avoid an endless loop that could occur when using an older version
         of localcharset.c. */
      if (code[0] == '\0')
        goto invalid;
      continue;
    }
    pool = stringpool;
    ap = aliases_lookup(buf,bp-buf);
    if (ap == NULL) {
      pool = stringpool2;
      ap = aliases2_lookup(buf);
      if (ap == NULL)
        goto invalid;
    }
    if (ap->encoding_index == ei_local_char) {
      code = locale_charset();
      /* Avoid an endless loop that could occur when using an older version
         of localcharset.c. */
      if (code[0] == '\0')
        goto invalid;
      continue;
    }
    if (ap->encoding_index == ei_local_wchar_t) {
      /* On systems which define __STDC_ISO_10646__, wchar_t is Unicode.
         This is also the case on native Woe32 systems.  */
#if __STDC_ISO_10646__ || ((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__)
      if (sizeof(wchar_t) == 4) {
        index = ei_ucs4internal;
        break;
      }
      if (sizeof(wchar_t) == 2) {
        index = ei_ucs2internal;
        break;
      }
      if (sizeof(wchar_t) == 1) {
        index = ei_iso8859_1;
        break;
      }
#endif
    }
    index = ap->encoding_index;
    break;
  }
  return all_canonical[index] + pool;
 invalid:
  return name;
}
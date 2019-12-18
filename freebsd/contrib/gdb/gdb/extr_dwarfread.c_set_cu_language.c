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
struct dieinfo {int at_language; int /*<<< orphan*/  at_name; } ;

/* Variables and functions */
#define  LANG_ADA83 137 
#define  LANG_C 136 
#define  LANG_C89 135 
#define  LANG_COBOL74 134 
#define  LANG_COBOL85 133 
#define  LANG_C_PLUS_PLUS 132 
#define  LANG_FORTRAN77 131 
#define  LANG_FORTRAN90 130 
#define  LANG_MODULA2 129 
#define  LANG_PASCAL83 128 
 int /*<<< orphan*/  cu_language ; 
 int /*<<< orphan*/  cu_language_defn ; 
 int /*<<< orphan*/  deduce_language_from_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  language_c ; 
 int /*<<< orphan*/  language_cplus ; 
 int /*<<< orphan*/  language_def (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  language_fortran ; 
 int /*<<< orphan*/  language_m2 ; 
 int /*<<< orphan*/  language_unknown ; 

__attribute__((used)) static void
set_cu_language (struct dieinfo *dip)
{
  switch (dip->at_language)
    {
    case LANG_C89:
    case LANG_C:
      cu_language = language_c;
      break;
    case LANG_C_PLUS_PLUS:
      cu_language = language_cplus;
      break;
    case LANG_MODULA2:
      cu_language = language_m2;
      break;
    case LANG_FORTRAN77:
    case LANG_FORTRAN90:
      cu_language = language_fortran;
      break;
    case LANG_ADA83:
    case LANG_COBOL74:
    case LANG_COBOL85:
    case LANG_PASCAL83:
      /* We don't know anything special about these yet. */
      cu_language = language_unknown;
      break;
    default:
      /* If no at_language, try to deduce one from the filename */
      cu_language = deduce_language_from_filename (dip->at_name);
      break;
    }
  cu_language_defn = language_def (cu_language);
}
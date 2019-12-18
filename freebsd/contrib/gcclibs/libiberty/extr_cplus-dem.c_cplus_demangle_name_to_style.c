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
struct demangler_engine {scalar_t__ demangling_style; int /*<<< orphan*/  demangling_style_name; } ;
typedef  enum demangling_styles { ____Placeholder_demangling_styles } demangling_styles ;

/* Variables and functions */
 struct demangler_engine* libiberty_demanglers ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unknown_demangling ; 

enum demangling_styles
cplus_demangle_name_to_style (const char *name)
{
  const struct demangler_engine *demangler = libiberty_demanglers; 

  for (; demangler->demangling_style != unknown_demangling; ++demangler)
    if (strcmp (name, demangler->demangling_style_name) == 0)
      return demangler->demangling_style;

  return unknown_demangling;
}
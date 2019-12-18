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
struct section_to_type {char type; scalar_t__ section; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct section_to_type* stt ; 

__attribute__((used)) static char
coff_section_type (const char *s)
{
  const struct section_to_type *t;

  for (t = &stt[0]; t->section; t++)
    if (!strncmp (s, t->section, strlen (t->section)))
      return t->type;

  return '?';
}
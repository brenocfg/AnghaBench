#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum language { ____Placeholder_language } language ;
struct TYPE_2__ {int la_language; int /*<<< orphan*/  la_name; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_STREQ (int /*<<< orphan*/ ,char*) ; 
 int language_unknown ; 
 TYPE_1__** languages ; 
 int languages_size ; 

enum language
language_enum (char *str)
{
  int i;

  for (i = 0; i < languages_size; i++)
    if (DEPRECATED_STREQ (languages[i]->la_name, str))
      return languages[i]->la_language;

  return language_unknown;
}
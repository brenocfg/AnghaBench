#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum language { ____Placeholder_language } language ;
struct TYPE_3__ {int la_language; } ;

/* Variables and functions */
 TYPE_1__* current_language ; 
 TYPE_1__** languages ; 
 int languages_size ; 
 int /*<<< orphan*/  set_lang_str () ; 
 int /*<<< orphan*/  set_type_range_case () ; 

enum language
set_language (enum language lang)
{
  int i;
  enum language prev_language;

  prev_language = current_language->la_language;

  for (i = 0; i < languages_size; i++)
    {
      if (languages[i]->la_language == lang)
	{
	  current_language = languages[i];
	  set_type_range_case ();
	  set_lang_str ();
	  break;
	}
    }

  return prev_language;
}
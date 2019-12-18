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
struct TYPE_2__ {int la_language; char* la_name; } ;

/* Variables and functions */
 TYPE_1__** languages ; 
 int languages_size ; 

char *
language_str (enum language lang)
{
  int i;

  for (i = 0; i < languages_size; i++)
    {
      if (languages[i]->la_language == lang)
	{
	  return languages[i]->la_name;
	}
    }
  return "Unknown";
}
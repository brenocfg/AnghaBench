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
struct language_defn {int la_language; } ;
typedef  enum language { ____Placeholder_language } language ;

/* Variables and functions */
 struct language_defn const** languages ; 
 int languages_size ; 

const struct language_defn *
language_def (enum language lang)
{
  int i;

  for (i = 0; i < languages_size; i++)
    {
      if (languages[i]->la_language == lang)
	{
	  return languages[i];
	}
    }
  return NULL;
}
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
struct curl_forms {scalar_t__ value; int /*<<< orphan*/  option; } ;

/* Variables and functions */
 scalar_t__ Curl_is_formadd_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
Curl_formadd_release_local(struct curl_forms * forms, int nargs, int skip)

{
  while(nargs--)
    if(nargs != skip)
      if(Curl_is_formadd_string(forms[nargs].option))
        if(forms[nargs].value)
          free((char *) forms[nargs].value);

  free((char *) forms);
}
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
typedef  int /*<<< orphan*/  regexp_t ;

/* Variables and functions */
 int /*<<< orphan*/  finish_regexp_representation () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  output_description_file ; 
 char* regexp_representation (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_regexp (regexp_t regexp)
{
  fprintf (output_description_file, "%s", regexp_representation (regexp));
  finish_regexp_representation ();
}
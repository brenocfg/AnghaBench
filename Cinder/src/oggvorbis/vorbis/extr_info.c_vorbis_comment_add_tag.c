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
typedef  int /*<<< orphan*/  vorbis_comment ;

/* Variables and functions */
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  vorbis_comment_add (int /*<<< orphan*/ *,char*) ; 

void vorbis_comment_add_tag(vorbis_comment *vc, const char *tag, const char *contents){
  char *comment=alloca(strlen(tag)+strlen(contents)+2); /* +2 for = and \0 */
  strcpy(comment, tag);
  strcat(comment, "=");
  strcat(comment, contents);
  vorbis_comment_add(vc, comment);
}
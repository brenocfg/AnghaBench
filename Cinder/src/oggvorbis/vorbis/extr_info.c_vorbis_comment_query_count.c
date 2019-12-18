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
struct TYPE_3__ {int comments; int /*<<< orphan*/ * user_comments; } ;
typedef  TYPE_1__ vorbis_comment ;

/* Variables and functions */
 char* alloca (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  tagcompare (int /*<<< orphan*/ ,char*,int) ; 

int vorbis_comment_query_count(vorbis_comment *vc, const char *tag){
  int i,count=0;
  int taglen = strlen(tag)+1; /* +1 for the = we append */
  char *fulltag = alloca(taglen+1);
  strcpy(fulltag,tag);
  strcat(fulltag, "=");

  for(i=0;i<vc->comments;i++){
    if(!tagcompare(vc->user_comments[i], fulltag, taglen))
      count++;
  }

  return count;
}
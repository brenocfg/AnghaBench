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
struct stoken {char* ptr; int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  msglist_len ; 
 char* msglist_sel ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

void
add_msglist(struct stoken *str, int addcolon)
{
  char *s, *p;
  int len, plen;

  if (str == 0) {		/* Unnamed arg, or...  */
    if (addcolon == 0) {	/* variable number of args.  */
      msglist_len++;
      return;
    }
    p = "";
    plen = 0;
  } else {
    p = str->ptr;
    plen = str->length;
  }
  len = plen + strlen(msglist_sel) + 2;
  s = (char *)xmalloc(len);
  strcpy(s, msglist_sel);
  strncat(s, p, plen);
  xfree(msglist_sel);
  msglist_sel = s;
  if (addcolon) {
    s[len-2] = ':';
    s[len-1] = 0;
    msglist_len++;
  } else
    s[len-2] = '\0';
}